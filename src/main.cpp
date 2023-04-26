#include "main.h"
#include "675A/match_autons.hpp"
using namespace pros;
// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    {-13, -12, 11},
    // Right Chassis Ports (negative port will reverse it!)
    {-20, 19, 18},
    // IMU Port
    2,
    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    2.75,
    // Cartridge RPM
    600,
    // External Gear Ratio
    .8);
void initialize() {
  master.clear();
  ez::print_ez_template();
  delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0);
  chassis.set_curve_default(0, 0);
  chassis_default_constants();
  chassis_exit_condition_defaults();
  ez::as::auton_selector.add_autons({
      Auton("Right Side 1", right_side_1),
  });
  chassis.initialize();
  ez::as::initialize();
  Task flywheel_task([&] { flywheel.fly_control(); });
  intake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {
  master.clear();
  flywheel.set_mode(3);
}

void competition_initialize() { master.clear(); }

void autonomous() {
  master.clear();
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  master.clear();
  flywheel.set_target(2300);
  flywheel.set_mode(1);
  Task drive_data_export_task(driver_data_export);
  Task flywheel_control_task(flywheel_toggle_function);
  Task speed_control_task(speed_toggle_function);
  Task tongue_control_task(tongue_control_toggle_function);
  Task intake_control_task(intake_control_toggle_function);
  Task speed_task(speed_control);
  Task endgame_control_task(endgame_control_function);
  Task drive_lock_control_task(drive_lock_control_function);
  // Task testing_speeds(set_speed_manually);
  while (true) {
    tongue_up_speed = 2300;
    tongue_down_speed = 2000;
    chassis.arcade_standard(ez::SPLIT);

    delay(ez::util::DELAY_TIME);
  }
}