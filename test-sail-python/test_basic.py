
import sophon.sail as sail
if __name__ == '__main__':
    dev_id = 0
    print("dev {} tpu-util is {} %".format(dev_id,sail.get_tpu_utli(dev_id)))

    print("get_vpu_utli",sail.get_vpu_utli(dev_id))

    print("get_vpp_utli",sail.get_vpp_utli(dev_id))
            
            
    print("get_board_temp",sail.get_board_temp(dev_id))
    
    print("get_chip_temp",sail.get_chip_temp(dev_id))

    print("get_dev_stat",sail.get_dev_stat(dev_id))