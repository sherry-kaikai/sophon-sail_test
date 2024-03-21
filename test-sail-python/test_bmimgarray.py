import sophon.sail as sail
handle = sail.Handle(1)
bmcv = sail.Bmcv(handle)
decoder = sail.Decoder("/data/jinyu.lu/jpu_test/1920x1080_yuvj420.jpg",True,1)
ori_img = decoder.read(handle)

# Create BMImageArray4D
images = sail.BMImageArray4D()
# Create BMImageArray4D with shape
images = sail.BMImageArray4D(handle, ori_img.height(), ori_img.width(), ori_img.format(), ori_img.dtype()) 

images.copy_from(0,ori_img)

images.attach_from(1,ori_img)

img_0 = images.__getitem__(0)
print("image0 from bmimg_array:",img_0.width(),img_0.height(),img_0.dtype())

images.__setitem__(3,ori_img.data())

devid = images.get_device_id()
print("device id:",devid)

