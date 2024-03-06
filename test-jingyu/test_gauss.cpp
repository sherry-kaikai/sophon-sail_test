#include <stdio.h>
#include <bmruntime_interface.h>
#include <bmlib_runtime.h>
#include <bmcv_api_ext.h>
// #include <bmcv_api.h>

#include "stdlib.h"
#include "string.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>

#include "bmlib_runtime.h"
#include "bmruntime_interface.h"
#include "bmruntime_cpp.h"

#define TIME_COST_US(start, end) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))
static int get_format_size(int format,int width, int height) {
    switch (format) {
        case FORMAT_RGB_PLANAR:
        case FORMAT_BGR_PLANAR:
        case FORMAT_RGB_PACKED:
        case FORMAT_BGR_PACKED:
        case FORMAT_RGBP_SEPARATE:
        case FORMAT_BGRP_SEPARATE:
            return width * height * 3;
        case FORMAT_GRAY:
            return width * height;
            break;
        default:
            printf("format error\n");
            return 0;
    }
}
    
static void write_bin(const char *output_path, unsigned char *output_data, int width, int height, int format) {
    FILE *fp_dst = fopen(output_path, "wb");
    if (fp_dst == NULL) {
        printf("无法打开输出文件 %s\n", output_path);
        return;
    }
    fwrite(output_data, sizeof(char), get_format_size(format, width, height), fp_dst);
    fclose(fp_dst);
}   
int main() {
    // 准备src和dst图像1
    int channel   = 1;
    int width     = 1920;
    int height    = 1080;
    int dev_id    = 1;
    bm_handle_t handle;
    bm_status_t dev_ret = bm_dev_request(&handle, dev_id);
    std::shared_ptr<float> src_ptr(
            new float[channel * width * height],
            std::default_delete<float[]>());
    std::shared_ptr<float> res_ptr(
            new float[channel * width * height],
            std::default_delete<float[]>());
    float * src_data = src_ptr.get();
    float * res_data = res_ptr.get();

    for(int i = 0; i < channel * width * height; i++) {
        src_data[i] = rand() % 255;
    }

    // bm_image bm_input, bm_output;
    // bm_image_create(handle,
    //                 height,
    //                 width,
    //                 FORMAT_GRAY,
    //                 DATA_TYPE_EXT_1N_BYTE,
    //                 &bm_input);
    // bm_image_alloc_dev_mem(bm_input);
    // bm_image_copy_host_to_device(bm_input, (void **)&src_data);
    // bm_image_create(handle,
    //                 height,
    //                 width,
    //                 FORMAT_GRAY,
    //                 DATA_TYPE_EXT_1N_BYTE,
    //                 &bm_output);
    // bm_image_alloc_dev_mem(bm_output);

    // 准备src和dst图像2
    cv::Mat input_img = cv::imread("/data/test_img.jpg",1,1);
    bm_image bm_input, bm_output;
    cv::bmcv::toBMI(input_img,&bm_input);

    bm_image_create(handle,
                    bm_input.height,
                    bm_input.width,
                    bm_input.image_format,
                    bm_input.data_type,
                    &bm_output);
    bm_image_alloc_dev_mem(bm_output);
    // 变换图片
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    if(BM_SUCCESS != bmcv_image_gaussian_blur(handle, bm_input, bm_output, 5, 5,3,0)){
        printf("error!");
        return -1;
    }
    else{
        printf("success!");
    }
    gettimeofday(&t2, NULL);
    printf("Gaussian_blur TPU using time = %ld(us)\n", TIME_COST_US(t1, t2));

    // 保存输出图片，验证
    cv::Mat cv_img;
    cv::bmcv::toMAT((bm_image *) &bm_output, cv_img, true); // 这里能取到output的数据吗，数据如果在device上？

    if (!cv::imwrite("./output_img1.jpg", cv_img)) {
            printf("error write");
        }

    bm_image_copy_device_to_host(bm_output, (void **)&res_data); //手动把device上的数据拷贝到host的buffer上，然后编码、保存，或者在h 2 d

    // 存储host数据到bin文件
    FILE *fp;
    fp = fopen ("./output.bin" , "wb+");
    if (NULL == fp) {
        std::cout << "open file failed!!" << std::endl;
        return BM_ERR_PARAM;
    }
    size_t data_size = width * height * 3; 
    fwrite (res_data , sizeof(unsigned char) , data_size , fp);
    fclose (fp);
    
    // bin文件中的数据再拷贝到bmimg，使其在host上获得数据
    bm_image_copy_host_to_device(bm_output, (void **)&res_data);
        // 保存输出图片，验证
    cv::Mat cv_img1;
    cv::bmcv::toMAT((bm_image *) &bm_output, cv_img1, true); // 这里能取到output的数据吗，数据如果在device上？

    if (!cv::imwrite("./output_img2.jpg", cv_img1)) {
            printf("error write");
        }
    //
    bm_image_destroy(bm_input);
    bm_image_destroy(bm_output);
    bm_dev_free(handle);

    return 0;
}