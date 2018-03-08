#ifndef LED13_H
#define LED13_H

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"

class Motor{
public:
	int ENA, IN1, IN2;
	Motor(int ENA, int IN1, int IN2);
	~Motor();
	run(int speed);
};

class RangeFinder{
public:
	int TRIG, ECHO;
	RangeFinder(int TRIG, int ECHO);
	~RangeFinder();
	distance();
}

class Vehicle{
public:
	Motor r_motor, l_motor;
	unsigned long previousMillis;
	Vehicle(Motor A, Motor B, ratio);
	~Vehicle();
	forward(int speed, unsigned long time_of_run);
	backward(int speed, unsigned long time_of_run);
	left(int angle);
	right(int angle);
	forward_left(int angle_rate, int speed, unsigned long time_of_run);
	forward_right(int angle_rate, int speed, unsigned long time_of_run);
	backward_left(int angle_rate, int speed, unsigned long time_of_run);
	backward_right(int angle_rate, int speed, unsigned long time_of_run);
	stop();
};


#endif


















