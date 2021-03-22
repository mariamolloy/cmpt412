#include <Pololu3piPlus32U4Buttons.h>
#include <Pololu3piPlus32U4Motors.h>
#include <Pololu3piPlus32U4LCD.h>
#include <Pololu3piPlus32U4IMU.h>
#include <Pololu3piPlus32U4.h> //import library
#include <Pololu3piPlus32U4Buzzer.h>


using namespace Pololu3piPlus32U4; //library

//what we want from library
Buzzer buzzer;
Motors motors;

//initialize ultrasonic
const int ECHO_PIN = 30;
const int TRIG_PIN = 17;

const int MAX_DISTANCE = 200; //200 cm or 2m

//ultrasonic timing
unsigned long currentMillis;
unsigned long prevMillis;
const unsigned long US_PERIOD = 100;

//current us distance reading
int distance = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN,OUTPUT);

  delay(1000);
  buzzer.play("c32");

}

void loop() {
  // put your main code here, to run repeatedly:
  usReadCm();
}

void usReadCm(){

  currentMillis = millis();
  if (currentMillis > prevMillis + US_PERIOD) {

    //clears trig_pin (set low)
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    //set trig_pin high (or active) or 10 microsecs
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    //last param is timeout
    long duration = pulseIn(ECHO_PIN, HIGH, 38000);
    //calculate distance
    distance = duration * 0.034 / 2; //using speed of sound

    //limits
    if (distance > MAX_DISTANCE) distance = MAX_DISTANCE;
    if (distance == 0) distance = MAX_DISTANCE;

    //print distance to serial monitor
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    //update prevMillis
    prevMillis = currentMillis;

  }
}
