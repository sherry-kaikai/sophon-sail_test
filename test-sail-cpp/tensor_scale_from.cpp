#include <iostream>
#include "tensor.h"

int main() {
    int dev_id = 0;
    int ret;
    sail::Handle handle(dev_id);
    std::shared_ptr<sail::Tensor> input_tensor1,input_tensor2;
    std::vector<int> input_shape = {10,10};
    bm_data_type_t input_dtype = BM_FLOAT32; // dtype can choose  BM_FLOAT32, BM_INT8, BM_UINT8, BM_INT32, BM_UINT32

    // init tensor
    input_tensor1 = std::make_shared<sail::Tensor>(input_shape, input_dtype);
    
    // prepare data
    std::shared_ptr<float> src_ptr(
            new float[10 * 10],
            std::default_delete<float[]>());
    float * src_data = src_ptr.get();
    for(int i = 0; i < 10 * 10; i++) {
        src_data[i] = rand() % 255;
    }

    // scale_to
    input_tensor1->scale_from(src_data, 0.1, 99); // scale data len is 99

    // 输出缩放后的数据
    for (int i = 0; i < size; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << std::endl;

    delete[] dst; // 释放内存

    return 0;
}