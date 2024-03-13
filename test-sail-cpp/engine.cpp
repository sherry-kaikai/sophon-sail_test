#include <iostream>
#include <fstream>
#include "engine.h"

int main() {  
        int dev_id = 0;
        sail::Handle handle(dev_id);
        
        std::string bmodel_path = "/data/jinyu.lu/yolov7_ipc/models/models/BM1684/lprnet_fp32_1b.bmodel";


        // 打开文件输入流
        std::ifstream file(bmodel_path, std::ios::binary);
        // 获取文件大小
        file.seekg(0, std::ios::end);
        size_t bmodel_size = file.tellg();
        file.seekg(0, std::ios::beg);

        // 分配内存来存储模型数据
        char* bmodel_ptr = new char[bmodel_size];
        // 读取文件内容到内存中
        file.read(bmodel_ptr, bmodel_size);
         // 关闭文件输入流
        file.close();
        sail::Engine engine5(bmodel_ptr, bmodel_size, dev_id, sail::SYSI);

        std::vector<std::string> bmodel_names = engine5.get_graph_names();
        std::vector<std::string> input_names = engine5.get_input_names(bmodel_names[0]);
        std::cout<<bmodel_names[0]<<input_names[0];
        return 0;  
    }
