
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

int main() {
    int channel   = 1;
    int width     = 1920;
    int height    = 1080;
    int dev_id    = 0;
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

    bm_image bm_input, bm_output;
    bm_image_create(handle,
                    height,
                    width,
                    FORMAT_GRAY,
                    DATA_TYPE_EXT_FLOAT32,
                    &bm_input);
    bm_image_alloc_dev_mem(bm_input);
    bm_image_copy_host_to_device(bm_input, (void **)&src_data);
    bm_image_create(handle,
                    height,
                    width,
                    FORMAT_GRAY,
                    DATA_TYPE_EXT_FLOAT32,
                    &bm_output);
    bm_image_alloc_dev_mem(bm_output);
    bm_device_mem_t hcoeff_mem;
    bm_device_mem_t wcoeff_mem;
    bm_malloc_device_byte(handle, &hcoeff_mem, height*height*sizeof(float));
    bm_malloc_device_byte(handle, &wcoeff_mem, width*width*sizeof(float));
    bmcv_dct_coeff(handle, bm_input.height, bm_input.width, hcoeff_mem, wcoeff_mem, true);
    bmcv_image_dct_with_coeff(handle, bm_input, hcoeff_mem, wcoeff_mem, bm_output);

    cv::Mat cv_img;
    cv::bmcv::toMAT((bm_image *) &bm_input, cv_img, true);

    if (!cv::imwrite("./output.jpg", cv_img)) {
            printf("error write");
        }

    bm_image_copy_device_to_host(bm_output, (void **)&res_data);
    bm_image_destroy(bm_input);
    bm_image_destroy(bm_output);
    bm_free_device(handle, hcoeff_mem);
    bm_free_device(handle, wcoeff_mem);
    bm_dev_free(handle);

    return 0;
}