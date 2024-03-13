#include <iostream>
#include "tensor.h"

using namespace std;

void test_if_success(int size, std::shared_ptr<sail::Tensor> output_tensor){
    // test if success
    float* dst = new float[size];
    output_tensor->scale_to(dst, 1); 
    for (int i = 0; i < 100; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << std::endl;
    delete[] dst; // 释放内存
}

int main() {
    int dev_id = 0;
    int ret;
    sail::Handle handle(dev_id);
    std::shared_ptr<sail::Tensor> input_tensor;
    std::vector<int> input_shape = {3, 1920, 1080};
    bm_data_type_t input_dtype = BM_FLOAT32;
    input_tensor = std::make_shared<sail::Tensor>(handle,input_shape, input_dtype,true,true);

    // 定义要设置的值
    std::shared_ptr<float> src_ptr(
            new float[3 * 1920 * 1080],
            std::default_delete<float[]>());
    float * src_data = src_ptr.get();
    for(int i = 0; i < 3 * 1920 * 1080; i++) {
        src_data[i] = rand() % 255;
    }
    // 输出一下src_data
    for (int i = 0; i < 100; ++i) {
        std::cout << src_data[i] << " ";
    }
    std::cout << std::endl;

    // memory set 到tensor
    input_tensor->memory_set(src_data);
    test_if_success(3 * 1920 * 1080,input_tensor); 


    // 这个是成功的
    // float value_ = 1.1;
    // input_tensor->memory_set(value_);
    // test_if_success(1,input_tensor);
    return 0;
}