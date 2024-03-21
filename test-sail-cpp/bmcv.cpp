#include <sail/cvwrapper.h>

// int main() {  
//     int dev_id = 0;
//     sail::Handle handle(dev_id);
//     // std::string image_name = "/home/jingyu/sophon-sail_test/test-sail-cpp/dog.jpg";
//     std::string image_name = "your_img.jpg";
//     sail::Decoder decoder(image_name, true, dev_id);
//     sail::BMImage BMimg_input = decoder.read(handle);
//     sail::BMImage BMimg_output;
//     sail::Bmcv bmcv(handle);
//     int ret = bmcv.gaussian_blur(BMimg_input,BMimg_output,3, 3, 0.1);
//     if(ret != 0){
//         std::cout << "gaussian_blur failed" << std::endl;
//         return -1;
//     }
//     bmcv.imwrite("output.jpg",BMimg_output);

//     return 0;  
// }
        

int main() {  
    int dev_id = 0;
    sail::Handle handle(dev_id);
    std::string image_name = "/home/jingyu/sophon-sail_test/test-sail-cpp/dog.jpg";
    // std::string image_name = "your_img.jpg";
    sail::Decoder decoder(image_name, true, dev_id);
    sail::BMImage BMimg_input = decoder.read(handle);

    sail::BMImage BMimg_output(handle,BMimg_input.height(),BMimg_input.width(),FORMAT_GRAY,DATA_TYPE_EXT_FLOAT32);
    
    sail::Bmcv bmcv(handle);
    int ret = bmcv.convert_format(BMimg_input,BMimg_output);
    

    ret = bmcv.DCT(BMimg_output,0);
    if(ret != 0){
        std::cout << "dct failed" << std::endl;
        return -1;
    }
    bmcv.imwrite("output.jpg",BMimg_output);

    return 0;  
}
        