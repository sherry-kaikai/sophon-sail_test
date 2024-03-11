import sophon.sail as sail


handle = sail.Handle(1)
bmcv = sail.Bmcv(handle)


bmimg = sail.BMImage()
decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,1)
bmimg = decoder.read(handle)

print("readed")
print(bmimg.format())
output = bmcv.Sobel(bmimg, 1, 1)

bmcv.imwrite("out.jpg",output)