import sophon.sail as sail
import os
if __name__ == '__main__':
    bmodel_path = "/data/jinyu.lu/yolov7_ipc/models/models/BM1684/lprnet_fp32_1b.bmodel"
    file = open(bmodel_path,"rb")
    datas = file.read()


    file_size = os.path.getsize(bmodel_path)
    print(file_size)
    sail.Engine(datas,file_size,0,sail.IOMode.SYSI)
