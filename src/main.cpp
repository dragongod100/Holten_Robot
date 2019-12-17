#include "lib.hpp"

auto drive = okapi::ChassisControllerFactory::create(
	{1_rmtr,2_rmtr}, {3_mtr,4_mtr},
	okapi::AbstractMotor::gearset::green,
	{4_in, 9.05_in});

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	set_brakes();
	
	tare();
	reset();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 // 129.5_deg = 1/4 turn LEFT
void autonomous()
{
	drive.moveDistance(9.125_in);
	drive.turnAngle(129.5_deg);
	drive.moveDistance(9_in);
	////////////////////////////
	move_rel(arm, 500);
	arm.move_velocity(3);
	drive.moveDistance(2.25_in);

	move_rel(extender, 14000, 500);
	move_rel(wrist, 300, 500);
	move_rel(claw, 100, 100);
	drive.moveDistance(-9_in);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	while (true)
	{
		driver();

		user_alt(wrist,DIGITAL_R2,DIGITAL_R1, DIGITAL_R2,DIGITAL_R1, 100);
		user_alt(extender,DIGITAL_UP,DIGITAL_DOWN, DIGITAL_UP,DIGITAL_DOWN, 600);
		user_alt(arm,DIGITAL_X,DIGITAL_B,DIGITAL_X,DIGITAL_B,100);
		user_alt(claw,DIGITAL_L1,DIGITAL_L2,DIGITAL_L1,DIGITAL_L2,100);
		pros::delay(20);

	}
}
