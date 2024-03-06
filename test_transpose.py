import sophon.sail as sail


handle = sail.Handle(0)
bmcv = sail.Bmcv(handle)
bmimg = sail.BMImage()
decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,0)
bmimg = decoder.read(handle)
img = bmcv.convert_format(bmimg,sail.Format.FORMAT_GRAY)
print("readed")
print(img.format())
output = bmcv.transpose(img)

bmcv.imwrite("out.jpg",output)