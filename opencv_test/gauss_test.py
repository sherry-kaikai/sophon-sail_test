import cv2
import numpy as np

img = cv2.imread("/data/test_img.jpg")

# size = img.shape
# # 对图像归一化处理
# img = img / 255
# gauss = np.random.normal(1, 0.01**0.05, size)
# img = img + gauss

# cv2.imwrite("cv_gauss.jpg",img)
img2 = cv2.GaussianBlur(img,(5, 5), 3,3)
cv2.imwrite("cv_output.jpg",img2)