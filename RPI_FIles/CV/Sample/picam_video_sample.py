import time
import picamera

with picamera.PiCamera() as camera:
    camera.resolution = (640, 360)
    camera.start_preview()
    camera.start_recording('my_video.h264')
    camera.wait_recording(30)
    camera.stop_recording()
    camera.stop_preview()
