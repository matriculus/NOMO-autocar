const int led = 13;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    light(Serial.read() - '0');
  }
  delay(500);
}
  
void light(int n)
{
  switch(n)
  {
    case 1:
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
      break;
      
    case 2:
      digitalWrite(led, HIGH);
      delay(2000);
      digitalWrite(led, LOW);
      delay(1000);
      break;
    
    case 3:
      digitalWrite(led, HIGH);
      delay(5000);
      digitalWrite(led, LOW);
      delay(1000);
      break;
  }
}
