// establishing pins for motor module

// motor one - left
int enA = 10;
int in1 = 9;
int in2 = 8;

// motor two - right
int enB = 5;
int in3 = 7;
int in4 = 6;

int sv = 2000;

void setup()
{
  // setting all the pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void forward(int spd)
{
  // this function runs the car forward
  // Both motors are set to high.
  // motor 1
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // setting speed for motor 1
  analogWrite(enA, 200);

  // motor 2
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  // setting speed for motor 1
  analogWrite(enB, 200);
  delay(spd);
  // switch off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);  
}
void backward(int spd)
{
  // this function runs the car backward
  // Both motors are set to high.
  // motor 1
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // setting speed for motor 1
  analogWrite(enA, 200);

  // motor 2
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  // setting speed for motor 1
  analogWrite(enB, 200);
  delay(spd);
  // switch off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0); 
}
void left(int spd)
{
  // this function runs the car left
  // Both motors are set to high.
  // motor 1
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // setting speed for motor 1
  analogWrite(enA, 0);

  // motor 2
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  // setting speed for motor 1
  analogWrite(enB, 200);
  delay(spd);
  // switch off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
void right(int spd)
{
  // this function runs the car right
  // Both motors are set to high.
  // motor 1
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // setting speed for motor 1
  analogWrite(enA, 200);

  // motor 2
  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
  // setting speed for motor 1
  analogWrite(enB, 0);
  delay(spd);
  // switch off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
void loop()
{
  forward(sv);
  delay(1000);
  backward(sv);
  delay(1000);
  left(sv);
  delay(1000);
  right(sv);
  delay(1000);
}
