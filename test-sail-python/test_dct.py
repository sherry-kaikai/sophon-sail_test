import sophon.sail as sail


handle = sail.Handle(1)
bmcv = sail.Bmcv(handle)


bmimg = sail.BMImage(handle,1080,1920,sail.Format.FORMAT_GRAY,sail.ImgDtype.DATA_TYPE_EXT_FLOAT32)

decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,1)
ori_img = decoder.read(handle)
print("readed")
print(ori_img.format(),ori_img.dtype())


img = bmcv.convert_format(ori_img,sail.Format.FORMAT_GRAY)

print(img.width(),img.height(),bmimg.width(),bmimg.height())
# bmcv.image_copy_to(img,bmimg,0,0) # 报错input data_type and image_format must be same to output!

bmcv.convert_to(img,bmimg,((1,0),(1,0),(1,0)))


output = bmcv.DCT(bmimg, 0)

bmcv.imwrite("out.jpg",output)