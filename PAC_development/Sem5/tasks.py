import os
import cv2

def shownails(image, mask):
    cv2.imshow('Image', image)
    cv2.imshow('Mask', mask)

    cv2.waitKey(0)

    cv2.destroyWindow('Image')
    cv2.destroyWindow('Mask')


def contours(image, mask):
    _, thresh = cv2.threshold(cv2.cvtColor(mask, cv2.COLOR_BGR2GRAY), 200, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    res = cv2.drawContours(image, contours, -1, (0, 255, 255), 1)

    cv2.imshow('Image+', res)
    cv2.waitKey(0)
    cv2.destroyWindow('Image+')


images = os.listdir("./images")

for i in images:
    im = cv2.imread(os.path.join("./images", i))
    msk = cv2.imread(os.path.join("./labels", i))

    #task2:
    # shownails(im, msk)


    # task3:
    # contours(im, msk)


    #task4:
    


cv2.destroyAllWindows()