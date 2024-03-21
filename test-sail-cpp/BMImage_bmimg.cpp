
#include <sail/cvwrapper.h>



// void copy_bm_img(const bm_image& src, bm_image& dest) {
//     dest.width = src.width;
//     dest.height = src.height;
    
//     dest.data = new char[src.width * src.height]; // 为新的结构体分配内存,但是bmimg没有data这个对外的接口，所以这里是错的

//     std::memcpy(dest.data, src.data, src.width * src.height); // 复制数据到新分配的内存
// }


int main() {
    int dev_id = 0;
    sail::Handle handle(dev_id);
    std::string image_name = "/data/jinyu.lu/sophon-demo/sample/SAM/datasets/kehu-test.jpg";
    sail::Decoder decoder(image_name, true, dev_id);
    sail::BMImage BMimg = decoder.read(handle);
    // Convert BMImage to bm_image data structure  
    bm_image bmimg = BMimg.data();  

    // // init BMImage from bm_image data structure
    // sail::BMImage BMimg2(bmimg);
    // std::cout << "Width: " << BMimg2.width() << ", Height: " << BMimg2.height() << ", Format: " << BMimg2.format() << ", Data Type: " << BMimg2.dtype() << std::endl;



    // memory copy1
    // bm_image bmimg2;
    // std::memcpy(&bmimg2, &bmimg, sizeof(bmimg)); // 使用 memcpy 函数来复制结构体
    // sail::BMImage BMimg3(bmimg2);
    // std::cout << "Width: " << BMimg3.width() << ", Height: " << BMimg3.height() << ", Format: " << BMimg3.format() << ", Data Type: " << BMimg3.dtype() << std::endl;


    // // memory copy2
    // bm_image bmimg2;
    // copy_bm_img(bmimg, bmimg2);

    return 0;  

}
