# import the necessary packages
import NOMO
import numpy as np
from picamera import PiCamera
from picamera.array import PiRGBArray
import time
import cv2
 
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (320, 240)
camera.hflip = True
camera.vflip = True
rawCapture = PiRGBArray(camera)
time.sleep(0.1)

last_time = time.time()
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	image = np.asarray(frame.array)
	new_screen, slopes, histogram = NOMO.process_image(image, perspective=True)
	print('Look took {} seconds.'.format(time.time()-last_time))
	last_time = time.time()
	cv2.imshow('Original', image)
	cv2.imshow('Image', new_screen)
	rawCapture.truncate(0)
	if cv2.waitKey(25) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break