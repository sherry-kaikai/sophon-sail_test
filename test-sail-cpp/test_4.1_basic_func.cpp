#include <iostream>
#include "engine_multi.h"

using namespace std;
int main() {
    // 4.1.1 
    int dev_len = sail::get_available_tpu_num();
    std::cout << "available dev num: " << dev_len << std::endl;

    // 4.1.2
    int ret = sail::set_print_flag(true);
    if (ret == 0){
        std::cout << "set print time success" << std::endl;
    }
    

    // 4.1.3
    ret = sail::set_dump_io_flag(true);
    if (ret == 0){
        std::cout << "set save data success" << std::endl;
    }

    // 4.1.7
    int tpu_util;
    tpu_util = sail::get_tpu_utli(0); //获取dev0的处理器使用率
    std::cout << "tpu_util " << tpu_util << "%"<< std::endl;

    // 4.1.8
    std::vector<int> vpu_util;
    vpu_util = sail::get_vpu_utli(0); //获取dev0的vpu处理器使用率

    for(int i = 0; i < vpu_util.size(); i++) {
        std::cout << "VPU ID: " << i << ", Util Value: " << vpu_util[i] << "%" << std::endl;
    }

    // 4.1.9
    std::vector<int> vpp_util;
    vpp_util = sail::get_vpp_utli(0); //获取dev0的vpp处理器使用率
    for(int i = 0; i < vpu_util.size(); i++) {
        std::cout << "VPP ID: " << i << ", Util Value: " << vpp_util[i] << "%" << std::endl;
    }


    return 0;
}