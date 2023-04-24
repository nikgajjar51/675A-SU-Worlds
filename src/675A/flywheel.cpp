#include "main.h"
using namespace pros;
void flywheel_controller::set_target(double target_speed) {
  flywheel_rpm_guard.take();
  flywheel_target_rpm = (double)target_speed;
  flywheel_rpm_guard.give();
}
void flywheel_controller::set_mode(int mode) {
  flywheel_mode_guard.take();
  if (mode == 1) {
    mode_ = 1;
  } else if (mode == 2) {
    mode_ = 2;
  } else if (mode == 3) {
    mode_ = 3;
  }
  flywheel_mode_guard.give();
}
void flywheel_controller::fly_control() {
  if (mode_ == 1) {
    bang_bang_control_function(flywheel_target_rpm);
  } else if (mode_ == 2) {
    flywheel_motor.move_voltage(12000);
  } else if (mode_ == 3) {
    flywheel_motor.move_voltage(0);
  }
}
void flywheel_controller::fire_discs() {}