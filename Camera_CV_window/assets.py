from settings import *
import pygame
import numpy as np
import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import RPi.GPIO as GPIO
import os

GPIO.setmode(GPIO.BCM)
pygame.init()

class Motor:
    def __init__(self, pins, freq=50):
        self.freq = freq
        en, self.in1, self.in2 = pins
        GPIO.setup(self.in1, GPIO.OUT)
        GPIO.setup(self.in2, GPIO.OUT)
        GPIO.setup(en, GPIO.OUT)
        self.forward()
        self.en = GPIO.PWM(en, self.freq) # helps to control the speed of the motor
        self.voltage = 0
        self.en.start(self.voltage)
    
    def run(self):
        self.en.ChangeDutyCycle(self.voltage)
    
    def forward(self):
        GPIO.output(self.in1, True)
        GPIO.output(self.in2, False)

    def reverse(self):
        GPIO.output(self.in1, False)
        GPIO.output(self.in2, True)
    
    def stop(self):
        self.voltage = 0
        self.en.ChangeDutyCycle(self.voltage)
    
    def changeVoltage(self, avolt):
        self.voltage += avolt
        self.voltage = max(0, self.voltage)
        self.voltage = min(self.voltage, 100)
    
    def stop_all(self):
        self.voltage = 0
        self.en.stop()
        GPIO.output(self.in1, False)
        GPIO.output(self.in2, False)
    
    def read_voltage(self):
        return self.voltage

class AutoCar:
    def __init__(self, motorA, motorB):
        self.freq = 50 # Hz
        self.motorLEFT = Motor(motorA, self.freq)
        self.motorRIGHT = Motor(motorB, self.freq) 
    
    def update(self):
        aleft, aright = 0, 0
        pressed = pygame.key.get_pressed()
        if pressed[pygame.K_LEFT] == 1:
            aleft = 20
            self.motorLEFT.changeVoltage(aleft)
            self.motorLEFT.run()
        else:
            aleft = -20
            self.motorLEFT.changeVoltage(aleft)
            self.motorLEFT.run()

        if pressed[pygame.K_RIGHT] == 1:
            aright = 20
            self.motorRIGHT.changeVoltage(aright)
            self.motorRIGHT.run()
        else:
            aright = -20
            self.motorRIGHT.changeVoltage(aright)
            self.motorRIGHT.run()
        
        if pressed[pygame.K_UP] == 1:
            self.motorLEFT.forward()
            self.motorRIGHT.forward()
        
        if pressed[pygame.K_DOWN] == 1:
            self.motorLEFT.reverse()
            self.motorRIGHT.reverse()
        
        if pressed[pygame.K_RSHIFT] == 1:
            self.motorLEFT.stop()
            self.motorRIGHT.stop()
        
        print("Left Velocity: {} % ------------- Right Velocity: {} %".format(self.read_data()[0], self.read_data()[1]))
    
    def stop_all(self):
        self.motorLEFT.stop_all()
        self.motorRIGHT.stop_all()
    
    def read_data(self):
        return self.motorLEFT.read_voltage(), self.motorRIGHT.read_voltage()

pygame.display.set_caption(window_title)
screen = pygame.display.set_mode(SIZE)

def transfer(file_x, file_y):
    '''
    This function transfers the file to the server pc securely and deletes the local copy of the file.
    '''
    x_transfer = "scp " + file_x + server + server_x_file + file_x + " &"
    y_transfer = "scp " + file_y + server + server_y_file + file_y + " &"
    os.system(x_transfer)
    os.system(y_transfer)
    os.system("rm " + file_x + " " + file_y)

def image_correction(frame):
    '''
    This function corrects the image by rotating and converting
    to numpy as also for a compatible format for pygame.
    '''
    image = np.asarray(frame.array)
    image = np.rot90(image)
    pyimage = pygame.surfarray.make_surface(image)
    return image, pyimage