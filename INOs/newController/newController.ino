#include <SXStepper.h>
#include <SXMotor.h>
#include<SXController.h>

const int stepsPerRev = 200;
const int rStepPin = 2; // STEP Pin is higher on the driver than DIR Pin
const int rDirPin = 3;
const int rCWValue = LOW;

const int gStepPin = 4;
const int gDirPin = 5;
const int gCWValue = LOW;

const int bStepPin = 6;
const int bDirPin = 7;
const int bCWValue = LOW;

SXController controller;
SXStepper stepperR(stepsPerRev, rStepPin, rDirPin, rCWValue);
SXStepper stepperG(stepsPerRev, gStepPin, gDirPin, gCWValue);
SXStepper stepperB(stepsPerRev, bStepPin, bDirPin, bCWValue);

const int cwPin = 12;
const int ccwPin = 11;
const int speedPin = 10;
const int sensorPin = A0;
SXMotor motor(speedPin, cwPin, ccwPin, sensorPin);
const int camSpeed = 175;

void setup() {
  // put your setup code here, to run once:
  controller.addStepper(&stepperR);
  controller.addStepper(&stepperG);
  controller.addStepper(&stepperB);
  stepperR.setSpeed(60);
  stepperG.setSpeed(60);
  stepperB.setSpeed(60);
  controller.addMotor(&motor);
  Serial.begin(9600);

//  delay(3000);
  
//  controller.calibrateMotor(camSpeed);
//  motor.moveUntilLight(camSpeed);
//  Serial.println("READY");
//  delay(3000);
  
}

int i = 0;
void loop() {
  while (i < 1) {
controller.goTo("HBF");
delay(5000);
controller.goTo("BBF");
delay(5000);
controller.goTo("BBE");
delay(5000);
controller.goTo("BBE");
delay(5000);
controller.goTo("BBE");
delay(5000);
controller.goTo("BAE");
delay(5000);
controller.goTo("BAE");
delay(5000);
controller.goTo("AAE");
delay(5000);
controller.goTo("AAE");
delay(5000);
controller.goTo("AAE");
delay(5000);
controller.goTo("AGE");
delay(5000);
controller.goTo("GGD");
delay(5000);
controller.goTo("GFD");
delay(5000);
controller.goTo("FFD");
delay(5000);
controller.goTo("GFE");
delay(5000);
controller.goTo("GFE");
delay(5000);
controller.goTo("FFF");
delay(5000);
controller.goTo("GGG");
delay(5000);
controller.goTo("GGA");
delay(5000);
controller.goTo("GGA");
delay(5000);
controller.goTo("GGA");
delay(5000);
controller.goTo("GGA");
delay(5000);
controller.goTo("FFG");
delay(5000);
controller.goTo("FFA");
delay(5000);

    i += 1;
  }
  motor.stop();
}
