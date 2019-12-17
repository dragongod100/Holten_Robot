
#include "main.h"
#include "okapi/api.hpp"
#include <cmath>
#include <algorithm>
using namespace okapi;
extern pros::Controller master;

extern pros::Motor wheel_r1;
extern pros::Motor wheel_r2;
extern pros::Motor wheel_l1;
extern pros::Motor wheel_l2;
extern pros::Motor arm;
extern pros::Motor extender;
extern pros::Motor claw;
extern pros::Motor wrist;
struct pid
{
  int error = 10;
  int sensor_value;
  int integral = 10;
  int derivative = 10;
  int prev_error;
  int power = 100;
};

// Begin drive.cpp
void user_control(pros::Motor motor,
  pros::controller_digital_e_t BUTTON_1,
  pros::controller_digital_e_t BUTTON_2, double VELOCITY);
void user_alt(pros::Motor motor, pros::controller_digital_e_t BUTTON_1,
  pros::controller_digital_e_t BUTTON_2, pros::controller_digital_e_t BUTTON_3,
  pros::controller_digital_e_t BUTTON_4, double VELOCITY);
void driver();
// End drive.cpp

// Begin auton.cpp
int PID(int setpoint, pros::Motor mo, int range,
  pid &pc, const double kP, const double kI, const double kD);
void move_rel(pros::Motor mo, const double setpoint, const double vel = 0);
void set_brakes();
void tare();
void reset();
// End auton.cpp
