from collections import deque
from imutils.video import VideoStream
import numpy as np
import cv2
import imutils
import time
from networktables import NetworkTables
import base64

NetworkTables.initialize(server = 'roborio-3637-frc.local')

sd = NetworkTables.getTable("SmartDashboard")

# height of the camera from the ground in inches
camHeight = 48
# diameter of the ball (inches)
ballDiameter = 9.5

# define the lower and upper boundaries of the ball in the HSV color space
lowerBound = (60, 0, 0)
upperBound = (100, 255, 255)

# initialize the list of tracked points
def pick_color(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDOWN:
        pixel = image_hsv[y,x]
        upper =  np.array([pixel[0] + 10, pixel[1] + 10, pixel[2] + 40])
        lower =  np.array([pixel[0] - 10, pixel[1] - 10, pixel[2] - 40])
        print(pixel, lower, upper)


# grab the reference to the webcam
vs = VideoStream(src=0).start()

# set the camera temperature
vs.stream.set(cv2.CAP_PROP_AUTO_WB, 0)
vs.stream.set(cv2.CAP_PROP_WB_TEMPERATURE, 10000)

# allow the camera to warm up
time.sleep(2.0)

count = -1

# keep looping
while True:
    # grab the current frame
    frame = vs.read()

    # resize the frame, blur it, and convert it to the HSV color space
    frame = imutils.resize(frame, width=600)
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

    # construct a mask for the color red, then perform dilations
    # and erosions to remove any small blobs left in the mask
    mask = cv2.inRange(hsv, lowerBound, upperBound)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)

    # find contours in the mask and initialize the current (x, y) center of the ball
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                        cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)
    center = None

    sentToDashboard = 0

    # only proceed if at least one contour was found
    for c in cnts:
        # find the largest contour in the mask, then use it
        # to compute the minimum enclosing circle and centroid
        c = max(cnts, key=cv2.contourArea)
        (x, y), radius = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

        # determine how circley the contour is
        a,b,w,h = cv2.boundingRect(c)
        aspectRatio = float(w) / h
        areaRatio = (np.pi * radius ** 2) / (float(w)*float(h))

        # only proceed if the circle is large and circley enough
        if radius > 5 and  aspectRatio > .9 and aspectRatio < 1.1 and areaRatio > .7 and areaRatio < .93:
            # find distance from the camera to the ball in inches, function of the ball's size in frame
            distance = (1933.2 * radius ** -.9403)
            # distance along the ground, from the intake to the ball
            groundDist = np.sqrt(distance ** 2 - camHeight ** 2)

            # horizontal offset in inches using a conversion factor
            pixelOffset = 300 - x
            offset = pixelOffset * (ballDiameter / (radius * 2))
            angle = -1 * np.degrees(np.arcsin(offset / groundDist))

            # draw the circle and centroid on the frame, then update the list of tracked points
            drawColor = (0, 255, 0) # green
            cv2.circle(frame, (int(x), int(y)), int(radius), drawColor, 2)
            cv2.circle(frame, center, 3, drawColor, -1)

            sd.putNumber("Distance", groundDist)
            sd.putNumber("Angle", angle)
            sentToDashboard = 1
            count = 0

    if sentToDashboard == 0:
        count += 1
        if count >= 8:
            # ball is untracked
            sd.putNumber("Distance", -1)
            sd.putNumber("X Offset", 100000)

    # put frames on screen
    cv2.namedWindow('Frame')
    cv2.setMouseCallback('Frame', pick_color)
    image_hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(1) & 0xFF

    cv2.namedWindow('Mask')
    cv2.imshow("Mask", mask)
    key = cv2.waitKey(1) & 0xFF

    # if the 'q' key is pressed, stop the loop
    if key == ord("q"):
        break

vs.release()

# close all windows
cv2.destroyAllWindows()
