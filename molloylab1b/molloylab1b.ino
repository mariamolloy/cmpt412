#include <Pololu3piPlus32U4Buttons.h>
#include <Pololu3piPlus32U4Motors.h>
#include <Pololu3piPlus32U4LCD.h>
#include <Pololu3piPlus32U4IMU.h>
#include <Pololu3piPlus32U4.h> //import library
#include <Pololu3piPlus32U4Buzzer.h>


using namespace Pololu3piPlus32U4; //library

//what we want from library
Encoders encoders;
Buzzer buzzer;
Motors motors;
ButtonA buttonA;

unsigned long currentMillis;
unsigned long prevMillis;
const unsigned long PERIOD = 20;

long countsLeft = 0;
long countsRight = 0;
long prevLeft = 0;
long prevRight = 0;

const int CLICKS_PER_ROTATION = 12;
const float GEAR_RATIO = 29.86F; //from pololu website
const float WHEEL_DIAMETER = 3.2; //from pololu 
const float WHEEL_CIRCUMFERENCE = 10.0531;

//global variables to keep track of total distance
float Sl = 0.0F;
float Sr = 0.0F;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  delay(1000); //so it waits a second before it starts bc it starts so quickly
  buzzer.play("c32"); //so u know it does something before it runs

}

void loop() {
  // put your main code here, to run repeatedly:


  
  checkEncoders0();
  checkEncoders1();
  //checkEncoders2();

 // buzzer.play("c32"); //beep beep
}


//move forward 12"
void checkEncoders0() {

  currentMillis = millis();
  if (currentMillis > prevMillis + PERIOD) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    
    //get the distance in cm 
    Sl += ((countsLeft - prevLeft) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);
    Sr += ((countsRight - prevRight) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);

    int wheelSpeed = 75;
   
    if (Sl < 30.5) {
      //if were near something start slowing down
      if (Sl > 20) {
        wheelSpeed = 70 * ((30 - Sl) / 10);
        //make sure we don’t slow down tooooooo much
        if (wheelSpeed < 30) {
          wheelSpeed = 30;
        }
      }
      motors.setSpeeds(wheelSpeed, wheelSpeed);
    
    }
    else {
      motors.setSpeeds(0,0);
    }
  Serial.print("Left: ");
  Serial.print(Sl);
  Serial.print("Right: ");
  Serial.print(Sr);

  prevLeft = countsLeft;
  prevRight = countsRight;
  prevMillis = currentMillis;
  
  }  
}

void checkEncoders1() {

  currentMillis = millis();
  if (currentMillis > prevMillis + PERIOD) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    
    //get the distance in cm 
    Sl += ((countsLeft - prevLeft) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);
    Sr += ((countsRight - prevRight) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);

    int wheelSpeed = 75;
   
    if (Sl > 0) {
      //if were near something start slowing down
      if (Sl < 15) {
        wheelSpeed = 70 * ((30 - Sl) / 10);
        //make sure we don’t slow down tooooooo much
        if (wheelSpeed < 30) {
          wheelSpeed = 30;
        }
      }
      motors.setSpeeds(wheelSpeed, wheelSpeed);
    
    }
    else {
      motors.setSpeeds(0,0);
    }
  Serial.print("Left: ");
  Serial.print(Sl);
  Serial.print("Right: ");
  Serial.print(Sr);

  prevLeft = countsLeft;
  prevRight = countsRight;
  prevMillis = currentMillis;
  
  }  
}

/**

//move backwards 12"
  void checkEncoders1() {

  currentMillis = millis();
  if (currentMillis > prevMillis + PERIOD) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    
    //get the distance in cm 
    Sl += ((countsLeft - prevLeft) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);
    Sr += ((countsRight - prevRight) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);

    int wheelSpeed = 75;
   
    if (Sl < 30.5) {
      //if were near something start slowing down
      if (Sl > 20) {
        wheelSpeed = 70 * ((30 - Sl) / 10);
        //make sure we don’t slow down tooooooo much
        if (wheelSpeed < 40) {
          wheelSpeed = 40;
        }
      }
      motors.setSpeeds(wheelSpeed, wheelSpeed);
    
    }
    else {
      motors.setSpeeds(0,0);
    }
  Serial.print("Left: ");
  Serial.print(Sl);
  Serial.print("Right: ");
  Serial.print(Sr);

  prevLeft = countsLeft;
  prevRight = countsRight;
  prevMillis = currentMillis;
  
  } 
  }
**/
  
//move forward 18"
   void checkEncoders2() {

  currentMillis = millis();
  if (currentMillis > prevMillis + PERIOD) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    
    //get the distance in cm 
    Sl += ((countsLeft - prevLeft) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);
    Sr += ((countsRight - prevRight) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);

    int wheelSpeed = 75;
   
    if (Sl < 46) {
      //if were near something start slowing down
      if (Sl > 37) {
        wheelSpeed = 70 * ((30 - Sl) / 10);
        //make sure we don’t slow down tooooooo much
        if (wheelSpeed < 40) {
          wheelSpeed = 40;
        }
      }
      motors.setSpeeds(wheelSpeed, wheelSpeed);
    
    }
    else {
      motors.setSpeeds(0,0);
    }
  Serial.print("Left: ");
  Serial.print(Sl);
  Serial.print("Right: ");
  Serial.print(Sr);

  prevLeft = countsLeft;
  prevRight = countsRight;
  prevMillis = currentMillis;
  
  }  
}
