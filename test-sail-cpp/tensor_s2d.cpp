#include <iostream>
#include "tensor.h"

using namespace std;
int main() {
    int dev_id = 0;
    int ret;
    sail::Handle handle(dev_id);
    std::shared_ptr<sail::Tensor> input_tensor;
    std::vector<int> input_shape = {10,10};
    bm_data_type_t input_dtype = BM_FLOAT32; 

    // init tensor
    input_tensor = std::make_shared<sail::Tensor>(handle, input_shape, input_dtype, true, true); // own sys mem:true, own dev mem:true
    // input_tensor = std::make_shared<sail::Tensor>(handle, input_shape, input_dtype, true, false); // own sys mem:true, own dev mem:false
    // prepare data
    input_tensor->ones();


    // input_tensor: own sys or dev data 
    bool _own_sys_data = input_tensor->own_sys_data();
    bool _own_dev_data = input_tensor->own_dev_data();
    std::cout << "input_tensor own_sys_data:" << _own_sys_data << std::endl;
    std::cout << "input_tensor own_dev_data:" << _own_dev_data << std::endl;
    // input_tensor -> sync_s2d(); // copy all data
    input_tensor -> sync_s2d(99); // copy part data
    _own_sys_data = input_tensor->own_sys_data();
    _own_dev_data = input_tensor->own_dev_data();
    std::cout << "input_tensor own_sys_data:" << _own_sys_data << std::endl;
    std::cout << "input_tensor own_dev_data:" << _own_dev_data << std::endl;
 
    // prepare another data: output_tensor, which is on sys mem, and don't have data
    // copy input_tensor to output_tensor
    // src is input_tensor, dst is output_tensor
    std::shared_ptr<sail::Tensor> output_tensor;
    output_tensor = std::make_shared<sail::Tensor>(handle, input_shape, input_dtype, true, true); 

    sail::Tensor& input_ref = *input_tensor;
    output_tensor -> sync_s2d(input_ref,2,3,10);

    output_tensor -> sync_d2s(); // must copy to system memory and save to dst
    // test if copy success
    int size = 100;
    float* dst = new float[size];
    output_tensor->scale_to(dst, 1, size); 
    for (int i = 0; i < size; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << std::endl;
    delete[] dst; // 释放内存

    return 0;
}