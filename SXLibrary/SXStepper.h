#ifndef SXStepper_h
#define SXStepper_h

class SXStepper
{
  public:
    SXStepper(int num_steps, int step_pin, int dir_pin, uint8_t cw_value);
    void setSpeed(long speed);
    void calculate(char target_note);
    void setDirection(String dir);
    bool isActive();
    void step();
    void setActive();

  private:
    int noteCharToPos(char target_note);

    // Setup
    int num_steps;
    int dir_pin;
    int step_pin;
    int cw_value;
    int ccw_value;

    // Controls Speed
    int step_delay;

    // Controls Movement
    bool active; // flags stepper to move
    int position; // current position
    String direction; // current movement direction
    int remaining_steps; // next movementl
};
#endif