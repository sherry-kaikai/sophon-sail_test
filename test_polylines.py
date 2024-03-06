import sophon.sail as sail


handle = sail.Handle(0)
bmcv = sail.Bmcv(handle)


bmimg = sail.BMImage()
decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,0)
bmimg = decoder.read(handle)

print("readed")

img = bmcv.convert_format(bmimg,sail.Format.FORMAT_GRAY)
ret = bmcv.polylines(img, [[(10,1000),(1900,1000),(1900,200)]], 1,(255,0,0),6,2)

print(ret)
bmcv.imwrite("out_ori.jpg",img)