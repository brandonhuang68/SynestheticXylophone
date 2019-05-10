#ifndef SXController_h
#define SXController_h

#define STEPPER_ARRAY_MAX 3

class SXController
{
  public:
  	SXController();
  	void addStepper(SXStepper *stepper_ptr);
    void addMotor(SXMotor *motor_ptr);
  	void moveAll();
  	void calculateAll(String notes);
    bool isActive();
  	bool isSteppersActive();
    bool isMotorActive();
    void goTo(String notes);
    void goTo(String notes, int motor_speed);
    void calibrateMotor(int motor_speed);

  private:
  	void stepAll();

  	SXStepper *stepper[STEPPER_ARRAY_MAX];
    SXMotor *motor;

    bool has_motor;
  	int num_steppers;
  	bool steppers_active;
    bool motor_active;
    bool active;
};

#endif
