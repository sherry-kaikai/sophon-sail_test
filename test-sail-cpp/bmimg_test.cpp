
#include <sail/cvwrapper.h>

int main() {
    int dev_id = 0;
    sail::Handle handle(dev_id);
    std::string image_name = "/data/jinyu.lu/sophon-demo/sample/SAM/datasets/kehu-test.jpg";
    sail::Decoder decoder(image_name, true, dev_id);
    sail::BMImage BMimg = decoder.read(handle);

    // Get the image information
    int width = BMimg.width();  
    int height = BMimg.height();  
    bm_image_format_ext format = BMimg.format();  
    bm_image_data_format_ext dtype = BMimg.dtype();  

    // Convert BMImage to bm_image data structure  
    bm_image bmimg = BMimg.data();  

    // init BMImage from bm_image data structure
    sail::BMImage BMimg2(bmimg);
    // Get the image information
    std::cout << "Width: " << BMimg2.width() << ", Height: " << BMimg2.height() << ", Format: " << BMimg2.format() << ", Data Type: " << BMimg2.dtype() << std::endl;

    // Get the device id and handle
    int device_id = BMimg.get_device_id();  
    int plane_num = BMimg.get_plane_num();  
    std::cout << "Width: " << width << ", Height: " << height << ", Format: " << format << ", Data Type: " << dtype << ", Device ID: " << device_id << ", Plane Num: " << plane_num << std::endl;  

    int ret;
    // Align the image  
    ret = BMimg.align();  
    if (ret != 0) {  
        std::cout << "Failed to align the image!" << std::endl;  
    }
    std::cout << "is align: " << BMimg.check_align() << std::endl;      

    // Unaling the image
    ret = BMimg.unalign();
    if (ret != 0) {  
        std::cout << "Failed to unalign the image!" << std::endl;    
    }
    std::cout << "is align: " << BMimg.check_align() << std::endl;

    // check contiguous memory
    std::cout << "is continues: " <<BMimg.check_contiguous_memory()<< std::endl;

    return 0;  

}



// #include "cvwrapper.h"
// #include <iostream>
// #include <string>

// using namespace std;
// using namespace sail;

// int main() {
//     string file_path = "/data/jinyu.lu/yolov7_ipc/data/licenseplate.mp4";
//     int tpu_id = 0;

//     Handle handle(tpu_id);
//     Decoder decoder(file_path, true, tpu_id);
//     BMImage image;
//     bm_image bm_img = image.data();
//     int ret = decoder.read_(handle, bm_img);
//     if (ret != 0) {
//         cerr << "Failed to read a frame!" << endl;
//         return ret;
//     }
//     cout << bm_img.height ;
//     return 0;
// }