#include <iostream>
#include "base64.h"

using namespace std;

int main() {
    // 4.1.4  base64_enc
    // init handle
    int dev_id = 0;
    int ret;
    sail::Handle handle(dev_id);

    std::string data = "hello,world!";

    // base64 encode
    std::string base64_encoded;
    uint32_t dlen = data.length();
    ret = sail::base64_enc(handle, data.c_str(), dlen, base64_encoded);
    if (ret == 0){
        std::cout << dlen << std::endl;
        std::cout << "base64 encode success!" << "based 64:" << base64_encoded << "lens" << dlen << std::endl;
    }

    // 4.1.5 base64_dec
    // std::string data_decoded;
    uint32_t dlen_based = base64_encoded.length();
    uint8_t out_data_buf[100]; // 假设有足够大的空间存放解码后的数据
    uint32_t out_data_size; // 用于存放解码后数据的长度
    ret =sail::base64_dec(handle, base64_encoded.c_str(), dlen_based, out_data_buf, &out_data_size);
    if (ret == 0){
        std::cout << "base64 decode success,data size is:" << out_data_size << std::endl;
        for(uint32_t i = 0; i < out_data_size; i++) {
            std::cout << out_data_buf[i];
        }
        std::cout << std::endl;
    }
    return 0;
}