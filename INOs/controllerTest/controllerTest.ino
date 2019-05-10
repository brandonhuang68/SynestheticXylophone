#include<SXStepper.h>
#include<SXStepperController.h>
#include<SXMotor.h>
#include<SXController.h>

//Stepper Motors
const int stepsPerRev = 200;
const int rStepPin = 3; // STEP Pin is higher on the driver than DIR Pin
const int rDirPin = 4;
const int rCWValue = LOW;

const int gStepPin = 5;
const int gDirPin = 6;
const int gCWValue = LOW;

const int bStepPin = 7;
const int bDirPin = 8;
const int bCWValue = LOW;

//Cam motor
const int speedPin = 9;
const int cwPin = 10;
const int ccwPin = 11;
const int sensorPin = A0;

//Controllers
SXController controller;
SXStepperController stepperController;

void setup() {
  //Stepper Setup
  SXStepper stepperR(stepsPerRev, rStepPin, rDirPin, rCWValue);
  SXStepper stepperG(stepsPerRev, gStepPin, gDirPin, gCWValue);
  SXStepper stepperB(stepsPerRev, bStepPin, bDirPin, bCWValue);
  stepperR.setSpeed(60);
  stepperG.setSpeed(60);
  stepperB.setSpeed(60);
  
  //Stepper Controller Setup
  stepperController.addStepper(&stepperR);
  stepperController.addStepper(&stepperG);
  stepperController.addStepper(&stepperB);

  //Motor Setup
  SXMotor motor(speedPin, cwPin, ccwPin, sensorPin);
  motor.setDirection("ccw");

  //Controller Setupt
  controller.addStepperController(&stepperController);
  controller.addMotor(&motor);
  controller.setSpeed(60);
  
  Serial.begin(9600);
}

void loop() {
  controller.play("CCC");
  controller.play("BEF");

}
