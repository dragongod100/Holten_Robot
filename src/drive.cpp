#include "lib.hpp"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::Motor wheel_r1 =
pros::Motor{1, MOTOR_GEARSET_18, true};

pros::Motor wheel_r2 =
pros::Motor{2, MOTOR_GEARSET_18, true};

pros::Motor wheel_l1 =
pros::Motor{3, MOTOR_GEARSET_18, false};

pros::Motor wheel_l2 =
pros::Motor{4, MOTOR_GEARSET_18, false};

pros::Motor arm =
pros::Motor{5, MOTOR_GEARSET_18, false};

pros::Motor extender =
pros::Motor{6, MOTOR_GEARSET_06, true};

pros::Motor claw =
pros::Motor{7, MOTOR_GEARSET_18, true};

pros::Motor wrist =
pros::Motor{9, MOTOR_GEARSET_36, true};

void user_control
(pros::Motor motor, pros::controller_digital_e_t BUTTON_1,
  pros::controller_digital_e_t BUTTON_2, double VELOCITY)
{
  if(master.get_digital(BUTTON_1))
  {
    motor.move_velocity(VELOCITY);
  }
  else if(master.get_digital(BUTTON_2))
  {
    motor.move_velocity(-VELOCITY);
  }
  else
  {
    motor.move_velocity(0);
  }
}

void user_alt(pros::Motor motor, pros::controller_digital_e_t BUTTON_1,
  pros::controller_digital_e_t BUTTON_2, pros::controller_digital_e_t BUTTON_3,
  pros::controller_digital_e_t BUTTON_4, double VELOCITY)
{
  if(master.get_digital(BUTTON_1))
  {
    motor.move_velocity(VELOCITY);
  }
  else if(master.get_digital(BUTTON_2))
  {
    motor.move_velocity(-VELOCITY);
  }
  else
  {
    if(partner.get_digital(BUTTON_1))
    {
      motor.move_velocity(VELOCITY);
    }
    else if(partner.get_digital(BUTTON_2))
    {
      motor.move_velocity(-VELOCITY);
    }
    else
    {
      motor.move_velocity(0);
    }
  }
}

void driver()
{
  if(abs(master.get_analog(ANALOG_LEFT_Y)) > 10)
  {
	    wheel_l1.move(master.get_analog(ANALOG_LEFT_Y));
    	wheel_l2.move(master.get_analog(ANALOG_LEFT_Y));
  }
  else if(abs(partner.get_analog(ANALOG_LEFT_Y)) > 10)
  {
	    wheel_l1.move(partner.get_analog(ANALOG_LEFT_Y));
    	wheel_l2.move(partner.get_analog(ANALOG_LEFT_Y));
  }
  else
  {
    wheel_l1.move(0);
    wheel_l2.move(0);
  }
  if(abs(master.get_analog(ANALOG_RIGHT_Y)) > 10)
  {
	    wheel_r1.move(master.get_analog(ANALOG_RIGHT_Y));
    	wheel_r2.move(master.get_analog(ANALOG_RIGHT_Y));
  }
  else if(abs(partner.get_analog(ANALOG_RIGHT_Y)) > 10)
  {
	    wheel_r1.move(partner.get_analog(ANALOG_RIGHT_Y));
    	wheel_r2.move(partner.get_analog(ANALOG_RIGHT_Y));
  }
  else
  {
    wheel_r1.move(0);
    wheel_r2.move(0);
  }
}
