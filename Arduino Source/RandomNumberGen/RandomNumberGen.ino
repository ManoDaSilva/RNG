/*
Random number generator
By Manoel da Silva

Idea from HotBits website, parts of code from coolsciencetech's instructable
Adapted by Pene for correcting hardware bias
*/

int time1;
int time2;
int counts = 0;
int interval[5];
boolean a;
boolean b;
boolean OK;

void setup() {
  //Booting up
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nStarting random generator");

  digitalWrite(3, HIGH);
  //Starting interrupt routine on pin 3
  attachInterrupt(0, count, FALLING);
}

void loop() {
  //Nothing to do in there!
}

void count() {
  detachInterrupt(0); //Turn off interrupts
  interval[counts] = micros(); //We store the current count into an array
  counts++;
  if (counts > 3) {
    time1 = interval[1] - interval[0];
    time2 = interval[3] - interval[4];
    if(!OK){
      if (time1 > time2) {
        a = false;
      }
      else if (time1 < time2) {
        a = true;
      }
      OK = true;
    } else {
      OK = false;
      if (time1 > time2) {
        b = false;
      }
      else if (time1 < time2) {
        b = true;
      }
      Serial.print(a^b);
    }
    counts = 0; //Reset the array counter
  }
  attachInterrupt(0, count, FALLING); //Restart interrupts
}
