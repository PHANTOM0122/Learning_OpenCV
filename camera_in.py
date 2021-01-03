import sys
import cv2

cap=cv2.VideoCapture('vtest.avi')

if not cap.isOpened():
    print('camera is not opened')
    sys.exit()

w = round(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
h = round(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)
fourcc = cv2.VideoWriter_fourcc(*'DIVX')
out = cv2.VideoWriter('output.avi',fourcc,fps,(w,h))

while True:
    ret, frame = cap.read()

    if not ret:
        break 

    edge = cv2.Canny(frame,50,150)
    edge = cv2.cvtColor(edge, cv2.COLOR_GRAY2BGR)
    out.write(edge)
    
    cv2.imshow('frame',frame)
    cv2.imshow('edge',edge)

    if cv2.waitKey(40) == 27:
        break

cap.release()
out.release()
cv2.destroyAllWindows()
