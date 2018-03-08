import time
import picamera
from fractions import Fraction

with picamera.PiCamera() as camera:
    camera.resolution = (640, 360)
    camera.hflip = True
    camera.vflip = True
    time.sleep(10)
    camera.exposure_mode = 'off'
    camera.framerate = 30
    camera.shutter_speed = camera.exposure_speed
    camera.iso = 1000
    camera.capture('foo.jpg')
