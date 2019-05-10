#include <Arduino.h>
#include "SXMotor.h"

#define CW "cw"
#define CCW "ccw"
#define DEFAULT_SENSOR_PIN A0
#define SENSOR_THRESHOLD 50

SXMotor::SXMotor(int speed_pin, int cw_pin, int ccw_pin)
{
	this->speed_pin = speed_pin;
	this->cw_pin = cw_pin;
	this->ccw_pin = ccw_pin;
	pinMode(speed_pin, OUTPUT);
  	pinMode(cw_pin, OUTPUT);
  	pinMode(ccw_pin, OUTPUT);
  	this->direction = CW;
  	this->sensor_pin = DEFAULT_SENSOR_PIN;
  	this->prev_sensor_reading = -1;
  	this->threshold = -1;
}

SXMotor::SXMotor(int speed_pin, int cw_pin, int ccw_pin, int sensor_pin)
{
	this->speed_pin = speed_pin;
	this->cw_pin = cw_pin;
	this->ccw_pin = ccw_pin;
	pinMode(speed_pin, OUTPUT);
  	pinMode(cw_pin, OUTPUT);
  	pinMode(ccw_pin, OUTPUT);
  	this->direction = CW;
  	this->sensor_pin = sensor_pin;
  	this->prev_sensor_reading = -1;
  	this->threshold = -1;
}

int SXMotor::getSensorReading()
{
	int num_readings = 10;
	int readings_sum = 0;
	for (int i = 0; i < num_readings; i++) {
		readings_sum += analogRead(this->sensor_pin);
	}
	return readings_sum/num_readings;
}

void SXMotor::setDirection(String dir)
{
	this->direction = dir;
}

void SXMotor::move(int speed)
{
	if (speed == 0) {
		this->active = false;
		analogWrite(speed_pin, 0);
		return;
	}
	this->active = true;
	analogWrite(speed_pin, speed);
	if (this->direction == CW) {
		digitalWrite(cw_pin, HIGH);
		digitalWrite(ccw_pin, LOW);
	} else if (this->direction == CCW) {
		digitalWrite(cw_pin, LOW);
		digitalWrite(ccw_pin, HIGH);
	}
}

bool SXMotor::isActive()
{
	return this->active;
}

void SXMotor::prepareMove()
{
	this->active = true;
	this->has_seen_dark = false;
	int reading = getSensorReading();
	if (reading > this->threshold) {
		this->starts_on_light = true;
	} else {
		this->starts_on_light = false;
		this->has_seen_dark = true;
	}
}

void SXMotor::update()
{
	this->active = true;
	int reading = getSensorReading();
	this->prev_sensor_reading = reading;
	if (this->starts_on_light && !this->has_seen_dark) {
		if (reading < threshold) {
			this->has_seen_dark = true;
		}
	} else if (this->starts_on_light && this->has_seen_dark) {
		if (reading > threshold) {
			stop();
		}
	} else if (!this->starts_on_light && this->has_seen_dark) {
		if (reading > threshold) {
			stop();
		}
	} else if (!this->starts_on_light && !this->has_seen_dark) {
		if (reading < threshold) {
			this->has_seen_dark = true;
		}
	}
}

void SXMotor::moveUntilLight(int speed)
{
	unsigned long timeout = 2000;
	unsigned long start_time = millis();


	prepareMove();
	while(isActive()) {
		if (millis() - start_time > timeout) {
			Serial.println("Timeout");
			break;
		}
		move(speed);
		update();
	}
	stop();
}

void SXMotor::stop()
{
	move(0);
	this->active = false;
}


void SXMotor::calibrate(int speed)
{
	int i = 0;
	move(speed);
	int reading;
	int low = 10000;
	int high = 0;
	while (i < 10000) {
		reading = analogRead(this->sensor_pin);
		if (reading > high) {
			high = reading;
		}
		if (reading < low) {
			low = reading;
		}
	    i++;
	}
	this->threshold = (int)((high - low) * 0.8) + low;
	move(0);
	Serial.println(high);
  	Serial.println(low);
  	Serial.println(this->threshold);
  	Serial.println("=======");
}

void SXMotor::setActive() {
	this->active = true;
}