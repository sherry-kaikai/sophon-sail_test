#include <iostream>
#include "tensor.h"

using namespace std;
int main() {
    int dev_id = 0;
    int ret;
    sail::Handle handle(dev_id);
    std::shared_ptr<sail::Tensor> input_tensor1,input_tensor2;
    std::vector<int> input_shape = {10,10};
    bm_data_type_t input_dtype = BM_FLOAT32; // dtype can choose  BM_FLOAT32, BM_INT8, BM_UINT8, BM_INT32, BM_UINT32

    // init tensor
    input_tensor1 = std::make_shared<sail::Tensor>(input_shape, input_dtype);
    input_tensor2 = std::make_shared<sail::Tensor>(handle, input_shape, input_dtype, true, true);
    
    // prepare data
    input_tensor1->ones();

    // get shape
    std::vector<int> tensor_shape;
    tensor_shape = input_tensor1->shape();
    std::cout << "tensor shape: ";
    for(int i = 0; i < tensor_shape.size(); i++) {
        std::cout << tensor_shape[i] << " ";
    }
    std::cout << std::endl;

    // 计算数据大小
    int size = 1;
    for (int dim : tensor_shape) {
        size *= dim;
    }

    // 准备一个与数据大小相等的数组来接收缩放后的数据
    float* dst = new float[size];

    // scale_to
    input_tensor1->scale_to(dst, 0.1, 99); // scale data len is 99

    // 输出缩放后的数据
    for (int i = 0; i < size; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << std::endl;

    delete[] dst; // 释放内存

    // // reshape
    input_tensor1->reshape({2,50}); // reshape from 10x10 to 2x50
    tensor_shape = input_tensor1->shape();
    std::cout << "tensor new shape: ";
    for(int i = 0; i < tensor_shape.size(); i++) {
        std::cout << tensor_shape[i] << " ";
    }
    std::cout << std::endl;

    // own sys or dev data 
    bool _own_sys_data = input_tensor1->own_sys_data();
    bool _own_dev_data = input_tensor1->own_dev_data();

    std::cout << "own_sys_data:" << _own_sys_data << std::endl;
    std::cout << "own_dev_data:" << _own_dev_data << std::endl;


    return 0;
}