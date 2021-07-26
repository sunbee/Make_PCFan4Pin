#include <Arduino.h>

#define FAN_CONTROLLER 3

int count = 0;
unsigned long start_time;
unsigned long tic = millis();
unsigned long toc = tic;
unsigned long delta = 0;
int RPM;
String speed_setting;

void counter() {
  count++;

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  Set up the pin no. 3 for controlling fan speed.
  The fan has a built in PWM controller, 
  so it should be enough to send a PWN signal.
  */
  pinMode(FAN_CONTROLLER, OUTPUT);
  analogWrite(FAN_CONTROLLER, 0);
  /*
  Set up pin no. 2 to receive interrupts
  in order to calculate the fan speed.
  */
  attachInterrupt(digitalPinToInterrupt(2), counter, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  start_time = millis();
  toc = millis();
  delta = toc - tic;
  count = 0;
  if (delta < 6000) {
    analogWrite(FAN_CONTROLLER, 0);
    speed_setting = "LOW";
  } else if ((delta > 6000) & (delta < 12000)) {
    analogWrite(FAN_CONTROLLER, 201);
    speed_setting = "MED";
  } else if ((delta > 12000) & (delta < 18000)) {
    analogWrite(FAN_CONTROLLER, 255);
    speed_setting = "HIGH";
  } else if (delta > 18000) {
    tic = toc;
  }
  while ((millis() - start_time) < 1000) {
    /* 
      Wait for 1 second.
      Meanwhile, interrupts are being rec'd
      on pin 2 and counter incremented.
    */
  }
  RPM = count * 60 / 2;
  Serial.print("Got RPM: ");
  Serial.print(RPM);
  Serial.print(" @ ");
  Serial.println(speed_setting);
}