int trig = 9;
int echo = 10;
int port = 9600;

class USRFinder
{
  int TRIG;
  int ECHO;
  int PORT;
  long duration;
  int distance;
  int trig_init = 2; // microseconds to initialise
  int trig_time = 10; // microseconds triggered
  int TRIGSTATE = LOW;
  bool istriggered = false;
  bool iscomputed = false;
  unsigned long prev_init;
  unsigned long prev_triggered;
  
  public:
    USRFinder(int trig, int echo, int port)
    {
      this->TRIG = trig;
      this->ECHO = echo;
      this->PORT = port;
      pinMode(this->TRIG, OUTPUT);
      pinMode(this->ECHO, INPUT);
      Serial.begin(this->PORT);
    }
    
    void set()
    {
      this->istriggered = true;
      this->prev_init = micros();
    }

    void compute()
    {
      if (this->istriggered){
        unsigned long curr_init = micros();
        if (curr_init - this->prev_init >= this->trig_init & this->TRIGSTATE == LOW & this->iscomputed == false){
          this->prev_init = curr_init;
          this->TRIGSTATE = HIGH;
          digitalWrite(this->TRIG, this->TRIGSTATE);
          this->prev_triggered = micros();
          this->iscomputed = true;
        }
        if (this->TRIGSTATE == HIGH){
          unsigned long current_triggered = micros();
          if (current_triggered - this->prev_triggered >= this->trig_time){
            this->prev_triggered = current_triggered;
            this->TRIGSTATE = LOW;
            digitalWrite(this->TRIG, this->TRIGSTATE);
          }
        }
        if (this->TRIGSTATE == LOW & this->iscomputed == true){
          this->duration = pulseIn(ECHO, HIGH);
          this->distance = duration * 0.034/2;
          Serial.print("Distance: ");
          Serial.println(this->distance);
          this->istriggered = false;
          this->iscomputed = false;
        }
      }
    }
};

void setup() {
  // put your setup code here, to run once:
}

int interval = 1; // milliseconds delay in switches
USRFinder usr(trig, echo, port);

unsigned long prevTT = millis();

void loop() {
  unsigned long currTT = millis();
  if (currTT - prevTT >= interval){
    prevTT = currTT;
    usr.set();
  }
  usr.compute();
}
