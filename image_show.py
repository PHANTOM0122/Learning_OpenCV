import sys
import cv2


img = cv2.imread('cat.bmp')

if img is None:
    print("Image load is failed!")
    sys.exit()

print(type(img))
print(img.shape)
print(img.dtype)

cv2.namedWindow('image')
cv2.imshow('image',img)
print
cv2.waitKey()
cv2.destoryAllWindows()
