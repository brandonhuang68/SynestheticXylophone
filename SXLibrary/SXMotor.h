#ifndef SXMotor_h
#define SXMotor_h

class SXMotor
{
	public:
		SXMotor(int speed_pin, int cw_pin, int ccw_pin);
		SXMotor(int speed_pin, int cw_pin, int ccw_pin, int sensor_pin);
		void setDirection(String dir);
		void move(int speed);
		void moveUntilLight(int speed);
		void calibrate(int speed);
		bool isActive();
		void prepareMove();
		void update();
		void stop();
		int getSensorReading();
		void setActive();
		// TODO: ADD SET BPM VIA TESTING
		int threshold;
	private:
		int speed_pin;
		int cw_pin;
		int ccw_pin;
		int sensor_pin;
		String direction;
		int prev_sensor_reading;

		bool active;
		bool starts_on_light;
		bool has_seen_dark;

};

#endif