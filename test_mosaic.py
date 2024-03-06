import sophon.sail as sail


handle = sail.Handle(0)
bmcv = sail.Bmcv(handle)


bmimg = sail.BMImage()
decoder = sail.Decoder("/data/1920x1080_yuvj420.jpg",True,0)
bmimg = decoder.read(handle)

print("readed")
ret = bmcv.mosaic(2, bmimg, [[10,10,100,2000],[500,500,1000,100]], 1)

print(ret)
bmcv.imwrite("out.jpg",bmimg)