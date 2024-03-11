import sophon.sail as sail


handle = sail.Handle(0)
bmcv = sail.Bmcv(handle)


bmimg = sail.BMImage()
decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,0)
bmimg = decoder.read(handle)

print("readed")
print(bmimg.format())
output = bmcv.gaussian_blur(bmimg, 3, 3, 0.1)

bmcv.imwrite("out.jpg",output)