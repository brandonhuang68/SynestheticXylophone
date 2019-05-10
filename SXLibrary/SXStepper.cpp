#include <Arduino.h>
#include "SXStepper.h"

#define DEFAULT_STEP_DELAY 500
#define CW "cw"
#define CCW "ccw"

//SX note positions
#define HOME_POS 0
#define B_POS 8
#define A_POS 16
#define G_POS 24
#define F_POS 32
#define E_POS 40
#define D_POS 48
#define C_POS 56


/*
 * 2-Wire Constructor intended for Palolo A4988 Stepper Driver.
 * cw_value should be HIGH or LOW depending on wiring of motor.
 */
SXStepper::SXStepper(int num_steps, int step_pin, int dir_pin, uint8_t cw_value)
{
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  this->step_pin = step_pin;
  this->dir_pin = dir_pin;
  this->num_steps = num_steps;
  this->step_delay = DEFAULT_STEP_DELAY;

  this->active = false;
  this->position = 0; // Assumes current position. This may need to be calibrated.
  this->remaining_steps = 0;
  this->direction = CW;

  // Steppers don't have consistent direction
  this->cw_value = cw_value;
  if (this->cw_value == HIGH) {
    this->ccw_value = LOW;
  } else {
    this->ccw_value = HIGH;
  }
}

/*
 * Sets the speed in revs per minute by setting the step_delay;
 * Taken from Arduino Stepper Library
 */
void SXStepper::setSpeed(long target_speed)
{
  this->step_delay = 60L * 1000L * 1000L / this->num_steps / target_speed /2L;
}

/*
 * Cacluates new movement for stepper.
 */
void SXStepper::calculate(char target_note)
{
  String dir;

  // Compute needed steps
  int target_position = noteCharToPos(target_note);
  int step_difference = target_position - this->position;

  // Do nothing and do not set stepper to active
  if (step_difference == 0) {
    return;
  }
  // Calculate direction
  if (step_difference > 0) {
    dir = CW;
  } else if (step_difference < 0){
    dir = CCW;
    step_difference = step_difference * -1;
  } else {
    this->active = false;
    return;
  }

  // Prepare this Stepper
  setActive();
  setDirection(dir);
  this->remaining_steps = step_difference;

}

/*
 * Set direction pin and for this Stepper
 */
void SXStepper::setDirection(String dir) {
  this->direction = dir;
  if (dir == CW) {
    digitalWrite(this->dir_pin, this->cw_value);
  } else if (dir == CCW) {
    digitalWrite(this->dir_pin, this->ccw_value);
  }
}

/*
 * Returns True if stepper is active.
 */
bool SXStepper::isActive() {
  return this->active;
}

void SXStepper::setActive() {
  this->active = true;
}

/*
 * Steps motor one step in direction of current direction.
 */
void SXStepper::step()
{
  if (!isActive()) {
    return;
  }
  digitalWrite(this->step_pin, HIGH);
  delayMicroseconds(this->step_delay);
  digitalWrite(this->step_pin, LOW);
  delayMicroseconds(this->step_delay);

  // Update this Stepper
  this->remaining_steps -= 1;
  if (this->direction == CW) {
    this->position += 1;
  } else if (this->direction == CCW) {
    this->position -= 1;
  }
  // Deactivate stepper if it has reached destination.
  if (this->remaining_steps <= 0) {
    this->active = false;
  }
}

int SXStepper::noteCharToPos(char target_note)
{
  int target_position;
  switch (target_note) {
    case 'H':
      target_position = HOME_POS;
    break;
    case 'B':
      target_position = B_POS;
    break;
    case 'A':
      target_position = A_POS;
    break;
    case 'G':
      target_position = G_POS;
    break;
    case 'F':
      target_position = F_POS;
    break;
    case 'E':
      target_position = E_POS;
    break;
    case 'D':
      target_position = D_POS;
    break;
    case 'C':
      target_position = C_POS;
    break;
  }
  return target_position;
}