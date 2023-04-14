#include "main.h"
using namespace pros;
// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    {11, 12, -13},
    // Right Chassis Ports (negative port will reverse it!)
    {-18, 19, 20},
    // IMU Port
    21,
    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    2.75,
    // Cartridge RPM
    600,
    // External Gear Ratio
    .8);
void initialize() {
  autonomous_data_export_task.suspend();
  drive_data_export_task.suspend();
  intake_task.suspend();
  endgame_task.suspend();
  ez::print_ez_template();
  delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);
  chassis_default_constants();
  chassis_exit_condition_defaults();
  ez::as::auton_selector.add_autons({
      Auton("Right Side 1", right_side_1),
  });
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {}
void competition_initialize() {}

void autonomous() {
  autonomous_data_export_task.resume();
  drive_data_export_task.suspend();
  intake_task.suspend();
  endgame_task.suspend();
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  autonomous_data_export_task.suspend();
  drive_data_export_task.resume();
  intake_task.resume();
  endgame_task.resume();
  chassis.set_drive_brake(E_MOTOR_BRAKE_HOLD);
  while (true) {
    flywheel_control_function();
    chassis.arcade_standard(ez::SPLIT);
    delay(ez::util::DELAY_TIME);
  }
}
