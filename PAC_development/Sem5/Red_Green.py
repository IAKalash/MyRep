import cv2
import numpy as np
import time

def main():
    cap = cv2.VideoCapture(0)

    _, prev = cap.read()
    prev = cv2.cvtColor(prev, cv2.COLOR_BGR2GRAY)

    height, width = prev.shape
    res = np.zeros((height, width, 3))

    green = True
    start = time.time()

    print(green, start)

    while True:
        ret, frame = cap.read()

        if (cv2.waitKey(1) == ord('q')):
            break

        elif ret:

            if (time.time() - start > 5):
                green = not green
                start = time.time()

            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            flow = cv2.calcOpticalFlowFarneback(prev, frame, None, 0.5, 2, 5, 3, 5, 1.2, 0)
            diff = cv2.magnitude(flow[..., 0], flow[..., 1])

            if green: 
                res[:]= (0,255, 0)
                cv2.putText(res, 'Green light', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)
            
            else:
                mask = diff > 3.0
                color = np.sum(mask)

                if color > 1500:
                    res[:] = (0, 0, 255)
                else:
                    res[:] = (0, 255, 0)

                cv2.putText(res, "Red light", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)


            cv2.imshow('cam', diff)
            cv2.imshow('colour', res)

            prev = frame


        else: break

    cap.release()

main()