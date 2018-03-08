#include "Rnomo.h"

Motor::Motor(int ENA, int IN1, int IN2)
{
	Motor.ENA = ENA;
	Motor.IN1 = IN1;
	Motor.IN2 = IN2;
	pinMode(Motor.ENA, OUTPUT);
	pinMode(Motor.IN1, OUTPUT);
	pinMode(Motor.IN2, OUTPUT);
}

void Motor::run(int speed, unsigned long time_of_run, ){

	unsigned long initialMillis = millis();



		if(speed<0){
			digitalWrite(Motor.IN1, LOW);
			digitalWrite(Motor.IN2, HIGH);
			analogWrite(Motor.ENA, abs(speed));
		}
		else{
			digitalWrite(Motor.IN1, HIGH);
			digitalWrite(Motor.IN2, LOW);
			analogWrite(Motor.ENA, speed);
		}
}

RangeFinder::RangeFinder(int TRIG, int ECHO){
	RangeFinder.TRIG = TRIG;
	RangeFinder.ECHO = ECHO;
	pinMode(RangeFinder.TRIG, OUTPUT);
	pinMode(RangeFinder.ECHO, INPUT);
}

float RangeFinder::distance(){
	digitalWrite(RangeFinder.TRIG,HIGH);
	delay(0.001);
	digitalWrite(RangeFinder.TRIG,LOW);

	while digitalRead(RangeFinder.ECHO) == 0{}
	start = millis();

	while digitalRead(RangeFinder.ECHO) == 1{}
	stop = millis();

	distance = (stop-start)* 17000;
	return distance;
}


Vehicle::Vehicle(Motor r_motor, Motor l_motor){
	unsigned long previousMillis = millis();
	Vehicle.r_motor = r_motor;
	Vehicle.l_motor = l_motor;
}

void Vehicle::forward(int speed, unsigned long time_of_run){
	

}



class Vehicle{
public:
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































