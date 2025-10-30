import cv2
import os
import random
import numpy as np

def rand_rotate(image, mask):

    height, width, _ = image.shape

    rot_mat = cv2.getRotationMatrix2D((height // 2, width // 2), random.randint(1, 360), 1.0)
    im = cv2.warpAffine(image, rot_mat, (height, width), flags=cv2.INTER_LINEAR)
    msk = cv2.warpAffine(mask, rot_mat, (height, width), flags=cv2.INTER_LINEAR)
    return im, msk

def rand_box(image, mask):

    height, width, _ = image.shape
    bbox = np.random.randint(0, min(height, width), size=4)

    im = image[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]
    msk = mask[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]
    return im, msk



def list_gen(len):
    images = os.listdir("../Sem5/images")
    while True:
        random.shuffle(images)
        image_list = []
        mask_list = []

        for i in images[:len]:
            im = cv2.imread(os.path.join("../Sem5/images", i))
            msk = cv2.imread(os.path.join("../Sem5/labels", i))

            match random.randint(1, 5):
                case 1:
                    im, msk = rand_rotate(im, msk)
                case 2:
                    im = im[::-1]
                    msk = msk[::-1]
                case 3:
                    im = im[:, ::-1]
                    msk = msk[:, ::-1]
                case 4:
                    im, msk = rand_box(im, msk)
                case 5:
                    im = cv2.medianBlur(im, 5)


            image_list.append(im)
            mask_list.append(msk)

        yield image_list, mask_list


def main():
    n = 5
    gen = list_gen(n)
    images, masks = next(gen)

    for i in range(n):
        # concat = cv2.hconcat([images[i], masks[i]])
        cv2.imshow('Image', images[i])
        cv2.imshow('mask', masks[i])

        cv2.waitKey(0)

        cv2.destroyWindow('Image')


main()