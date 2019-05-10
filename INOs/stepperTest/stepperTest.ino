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

void setup() {
  // put your setup code here, to run once:
  controller.addStepper(&stepperR);
  controller.addStepper(&stepperG);
  controller.addStepper(&stepperB);
  stepperR.setSpeed(60);
  stepperG.setSpeed(60);
  stepperB.setSpeed(60);
  
  Serial.begin(9600);
}

int i = 0;
void loop() {
  delay(3000);
  while (i < 10) {
    controller.goTo("HHH");
    delay(1000);
    controller.goTo("BBB");
    delay(1000);
    controller.goTo("AAA");
    delay(1000);
    controller.goTo("GGG");
    delay(1000);
    controller.goTo("FFF");
    delay(1000);
    controller.goTo("EEE");
    delay(1000);
    controller.goTo("DDD");
    delay(1000);
    controller.goTo("CCC");
    delay(1000);
    i += 1;
    Serial.println("End");
  }
}


//int i = 0;
//void loop() {
//  while (i < 1) {
//    stepperR.calculate('B');
//    stepperG.calculate('C');
//    while(stepperR.isActive()) {
//      stepperR.step();
//    }
//    while(stepperG.isActive()) {
//      stepperG.step();
//    }
//    stepperR.calculate('H');
//    stepperG.calculate('D');
//    while(stepperR.isActive()) {
//      stepperR.step();
//    }
//    while(stepperG.isActive()) {
//      stepperG.step();
//    }
//    i += 1;
//  }
//}
