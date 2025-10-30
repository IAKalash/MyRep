import os
import cv2

def shownails(image, mask):
    concat = cv2.vconcat([image, mask])
    cv2.imshow('Image', concat)

    cv2.waitKey(0)

    cv2.destroyWindow('Image')


def contours(image, mask):
    _, thresh = cv2.threshold(cv2.cvtColor(mask, cv2.COLOR_BGR2GRAY), 200, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    res = cv2.drawContours(image, contours, -1, (0, 255, 255), 1)

    cv2.imshow('Image+', res)
    cv2.waitKey(0)
    cv2.destroyWindow('Image+')

def showVideo():
    cap = cv2.VideoCapture("./Запись экрана от 2025-10-09 09-55-19.webm")

    while True:
        _, frame = cap.read()
        if frame is not None:
            resize = cv2.resize(frame, (1000, 500))

        cv2.imshow('Video', cv2.cvtColor(resize, cv2.COLOR_BGR2GRAY))

        if cv2.waitKey(1) == ord('q'): 
            break

    cap.release()


def main():

    images = os.listdir("./images")

    for i in images:
        im = cv2.imread(os.path.join("./images", i))
        msk = cv2.imread(os.path.join("./labels", i))


        #task2:
        shownails(im, msk)


        # task3:
        # contours(im, msk)


    # task4:
    # showVideo()
    
    cv2.destroyAllWindows()

main()