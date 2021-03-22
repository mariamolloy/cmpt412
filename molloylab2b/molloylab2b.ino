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

const int MAX_DISTANCE = 100.0; //in cm

//normalization
const float DISTANCE_FACTOR = MAX_DISTANCE / 100;
const float STOP_DISTANCE = 10; //min distance between robot and object

//motors
const float MOTOR_BASE_SPEED = 300.0; //switch to 300 later
const int MOTOR_MIN_SPEED = 30; //dont want to stall
//normalization based on base speed
const float MOTOR_FACTOR = MOTOR_BASE_SPEED / 100;

//ultrasonic timing
unsigned long usCm; //ultrasonic current millis
unsigned long usPm; //ultrasonic previous millis
const unsigned long US_PERIOD = 50;

//motor timing
unsigned long mCm; //motor current millis
unsigned long mPm; //motor previous millis
const unsigned long MOTOR_PERIOD = 20;

//current ultrasonic distance reading
float distance = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN,OUTPUT);

  delay(1000);
  buzzer.play("c32");

}

void loop() {
  // put your main code here, to run repeatedly:
  usReadCm(); //read distance

  setMotors(); //update motor speeds
}


//function to read and update the current ulstrasonic distance
void usReadCm(){

  usCm = millis();
  if (usCm > usPm + US_PERIOD) {

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
    Serial.println("distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    //update previous Millis
    usPm = usCm;

  }
}


//function to set the motor speed
void setMotors(){
  mCm = millis();
  if (mCm > mPm + MOTOR_PERIOD) {
    //set base speeds 
    float leftSpeed = MOTOR_BASE_SPEED;
    float rightSpeed = MOTOR_BASE_SPEED;

    //check that current distance is <= Max distance otherwise we dont have to do anything
    if (distance <= MAX_DISTANCE) {

      //magnitude is like nice linear percentage of distance
      //short distance = high magnitude
      float magnitude = (float)(MAX_DISTANCE - distance) / DISTANCE_FACTOR;

      leftSpeed = MOTOR_BASE_SPEED - (magnitude * MOTOR_FACTOR);
      rightSpeed = MOTOR_BASE_SPEED - (magnitude * MOTOR_FACTOR);
    }

      
      //check we dont dip below min speed and stall
      if (leftSpeed < MOTOR_MIN_SPEED) leftSpeed = MOTOR_MIN_SPEED;
      if (rightSpeed < MOTOR_MIN_SPEED) rightSpeed = MOTOR_MIN_SPEED;

      //check stop distance and stop motors
      if (distance <= STOP_DISTANCE){
        leftSpeed = 0;
        rightSpeed = 0;
      }

      Serial.print("Left: ");
      Serial.print(leftSpeed);
      Serial.print(" Right: ");
      Serial.println(rightSpeed);

      //set motors and reset millis
      motors.setSpeeds(leftSpeed, rightSpeed);
      mPm = mCm;
      
  }
}
