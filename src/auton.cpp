#include "lib.hpp"
pid a;
pid b;
pid c;
int PID(int setpoint, pros::Motor mo, int range,
  pid &pc, float kP, float kI, float kD)
{
  pc.error = setpoint - mo.get_position();
  pc.integral = pc.integral + pc.error;
  if(abs(pc.error) > range || pc.error == 0)
  {
    pc.integral = 0;
  }
  pc.derivative = pc.error - pc.prev_error;
  pc.prev_error = pc.error;
  pc.power = pc.error * kP + pc.integral * kI + pc.derivative * kD;
  mo.move_velocity(pc.power);
  return pc.power;
}

int pid_drive(int setpoint, pros::Motor mo_0, pros::Motor mo_1, int range,
  pid &pc, const double kP, const double kI, const double kD)
{
  pc.error = setpoint - mo_0.get_position();
  pc.integral = pc.integral + pc.error;
  if(abs(pc.error) > range || pc.error == 0)
  {
    pc.integral = 0;
  }
  pc.derivative = pc.error - pc.prev_error;
  pc.prev_error = pc.error;
  pc.power = pc.error * kP + pc.integral * kI + pc.derivative * kD;
  mo_0.move_velocity(pc.power);
  mo_1.move_velocity(pc.power);
  return pc.power;
}

void move_rel(pros::Motor mo, const double setpoint, const double vel)
{
  if(vel == 0)
  {
    mo.move_absolute(setpoint, 600);
  }
  else
  {
    mo.move_absolute(setpoint, vel);
  }
	while (!((mo.get_position() < (setpoint + 5)) && (mo.get_position() > (setpoint - 5))))
	{
		pros::delay(2);
	}
  mo.tare_position();
}

void set_brakes()
{
  arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  wrist.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void tare()
{
	wheel_l1.tare_position();
	wheel_l2.tare_position();
	wheel_r1.tare_position();
	wheel_r2.tare_position();
	arm.tare_position();
	extender.tare_position();
	claw.tare_position();
	wrist.tare_position();
}

void reset()
{

}
