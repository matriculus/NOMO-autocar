class Flasher
{
  int ledPin;
  long OnTime;
  long OffTime;

  int ledState;
  unsigned long previousMillis;

  public:
  Flasher(int pin, long on, int speed1)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);

    OnTime = on;
    mspeed = speed1;

    ledState = LOW;
    previousMillis = 0;
  }

  void update()
  {
    unsigned long currentMillis = millis();
    if((currentMillis-previousMillis>=OnTime))
    {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
    else
    {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
};

Flasher led1(8, 400, speed1);

void setup(){
}

void loop()
{
  led1.update();
}

