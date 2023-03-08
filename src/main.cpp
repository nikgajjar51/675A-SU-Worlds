#include "main.h"
using namespace pros;
// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    {2, 5},
    // Right Chassis Ports (negative port will reverse it!)
    {-3, -4},
    // IMU Port
    21,
    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    3.25,
    // Cartridge RPM
    600,
    // External Gear Ratio
    1);
void initialize() {
  ez::print_ez_template();
  delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0);
  chassis.set_curve_default(0, 0);
  chassis_default_constants();
  chassis_exit_condition_defaults();
  ez::as::auton_selector.add_autons({});
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {}
void competition_initialize() {}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  while (true) {
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    delay(ez::util::DELAY_TIME);  // This is used for timer calculations!
                                        // Keep this ez::util::DELAY_TIME
  }
}
