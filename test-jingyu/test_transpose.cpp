#include <stdio.h>
// #include "bmcv_api_ext_c.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
#include "opencv2/opencv.hpp"
#include "bmruntime_interface.h"
#include "bmruntime_cpp.h"
#include <iostream>
#include <vector>
#include "bmcv_api_ext.h"
// #include "bmlib_utils.h"
// #include "common.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <memory>
typedef uint8_t u8;
int main(int argc, char *argv[]) {
    bm_handle_t handle;
    bm_dev_request(&handle, 0);

    int image_n = 1;
    int image_h = 1080;
    int image_w = 1920;
    bm_image src, dst;
    bm_image_create(handle, image_h, image_w, FORMAT_RGB_PLANAR,
            DATA_TYPE_EXT_1N_BYTE, &src);
    bm_image_create(handle, image_w, image_h, FORMAT_RGB_PLANAR,
            DATA_TYPE_EXT_1N_BYTE, &dst);

    std::shared_ptr<u8*> src_ptr = std::make_shared<u8*>(
            new u8[image_h * image_w * 3]);
    memset((void *)(*src_ptr.get()), 148, image_h * image_w * 3);


    u8 *host_ptr[] = {*src_ptr.get()};
    bm_image_copy_host_to_device(src, (void **)host_ptr); // 用host的数据填充到src的bm_image里面
    bmcv_image_transpose(handle, src, dst);

    cv::Mat cv_img;
    cv::bmcv::toMAT((bm_image *) &dst, cv_img, true);

    if (!cv::imwrite("./output.jpg", cv_img)) {
            printf("error write");
        }


    bm_image_destroy(src);
    bm_image_destroy(dst);
    bm_dev_free(handle);
    return 0;
}