import cv2
import numpy as np

def main():
    image = cv2.imread('./ghosts/lab7.png')

    sift = cv2.SIFT_create()

    scene_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    kp_scene, des_scene = sift.detectAndCompute(scene_gray, None)

    for i in range(6):
        match i:
            case 0:
                ghost = cv2.imread("./ghosts/candy_ghost.png", cv2.IMREAD_GRAYSCALE)
            case 1:
                ghost = cv2.imread("./ghosts/candy_ghost.png", cv2.IMREAD_GRAYSCALE)
            case 2:
                ghost = cv2.imread("./ghosts/candy_ghost.png", cv2.IMREAD_GRAYSCALE)
            case 3:
                ghost = cv2.imread("./ghosts/scary_ghost.png", cv2.IMREAD_GRAYSCALE)
            case 4:
                ghost = cv2.flip(cv2.imread("./ghosts/scary_ghost.png", cv2.IMREAD_GRAYSCALE), 1)
            case 5:
                ghost = cv2.imread("./ghosts/pampkin_ghost.png", cv2.IMREAD_GRAYSCALE)

        kp_ghost, des_ghost = sift.detectAndCompute(ghost, None)

        matcher = cv2.FlannBasedMatcher(dict(algorithm=1, trees=5), dict(checks=50))

        matches = matcher.knnMatch(des_ghost, des_scene, k=2)

        good_matches = []
        for m, n in matches:
            if m.distance < 0.75 * n.distance:
                good_matches.append(m)

        src_pts = np.float32([kp_ghost[m.queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
        dst_pts = np.float32([kp_scene[m.trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)

        H, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)

        h, w = ghost.shape
        ghost_corners = np.float32([[0, 0], [0, h-1], [w-1, h-1], [w-1, 0]]).reshape(-1, 1, 2)
        scene_corners = cv2.perspectiveTransform(ghost_corners, H)
        cv2.polylines(image, [np.int32(scene_corners)], True, (0, 255, 0), 3, cv2.LINE_AA)

        mask = mask.ravel().tolist()
        used_scene_indices = [good_matches[i].trainIdx for i in range(len(good_matches)) if mask[i] == 1]
        keep_scene_mask = np.ones(len(kp_scene), dtype=bool)
        keep_scene_mask[used_scene_indices] = False
        kp_scene = [kp_scene[j] for j in range(len(kp_scene)) if keep_scene_mask[j]]
        des_scene = des_scene[keep_scene_mask]

    cv2.imshow('result', cv2.resize(image, (1000, 500)))
    cv2.waitKey(0)
    cv2.destroyAllWindows()

main()