#include <Arduino.h>
#include "SXStepper.h"
#include "SXMotor.h"
#include "SXController.h"

#define STEPPER_ARRAY_MAX 3

SXController::SXController()
{
  for (int i = 0; i < STEPPER_ARRAY_MAX; i++) {
    stepper[i] = 0;
  }
  int num_steppers = 0;
  bool active = false;
  bool steppers_active = false;
  bool motor_active = false;
  bool ready = false;
  bool has_motor = false;
}

void SXController::calculateAll(String notes)
{
  for (int i = 0; i < notes.length(); i++) {
    stepper[i]->calculate(notes[i]);
    if (stepper[i]->isActive()) {
      this->steppers_active = true;
    }
  }
}
bool SXController::isActive()
{
  return isSteppersActive() || isMotorActive();
}
bool SXController::isSteppersActive()
{
  return this->steppers_active;
}
bool SXController::isMotorActive()
{
  if (this->has_motor) {
    return motor->isActive();
  } else {
    return false;
  }
}

void SXController::addStepper(SXStepper *stepper_ptr)
{
  for (int i = 0; i < STEPPER_ARRAY_MAX; i++) {
    if (stepper[i] == 0) {
      stepper[i] = stepper_ptr;
      this->num_steppers += 1;
      break;
    }
  }
}

void SXController::addMotor(SXMotor *motor_ptr)
{
  motor = motor_ptr;
  this->has_motor = true;
}

void SXController::stepAll()
{
  this->steppers_active = false;
  for (int i = 0; i < this->num_steppers; i++) {
    if (stepper[i]->isActive()) {
      stepper[i]->step();
      if (stepper[i]->isActive()) {
        this->steppers_active = true;
      }
    }
  }
}

void SXController::moveAll()
{
  while(isSteppersActive()) {
    stepAll();
  }
}

void SXController::goTo(String notes)
{
  calculateAll(notes);
  moveAll();
}

void SXController::goTo(String notes, int motor_speed)
{
  Serial.println(notes);
  calculateAll(notes);
  moveAll();
  motor->setActive();
  if (this->has_motor) {
    Serial.println("move motor");
      motor->moveUntilLight(motor_speed);
      delay(1000);
  }
  
}

void SXController::calibrateMotor(int motor_speed)
{
  if (this->has_motor) {
    motor->calibrate(motor_speed);
  }
}