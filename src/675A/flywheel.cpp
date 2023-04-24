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
  uint32_t t = pros::millis();

  while (true){
    if (mode_ == 1) {
      if ((get_flywheel_velocity() * 6) < flywheel_target_rpm) {
        flywheel_motor.move_voltage(12000);
      } else {
        flywheel_motor.move_voltage((flywheel_target_rpm / 3600) * 12000);
      }
    } else if (mode_ == 2) {
      flywheel_motor.move_voltage(12000);
    } else if (mode_ == 3) {
      flywheel_motor.move_voltage(0);
    }

    pros::Task::delay_until(&t, 10);
  }
}

void flywheel_controller::fire_discs(int numDisk, int fireTime) {
    set_mode(1);

    for (int i = 0; i < numDisk; i++) {
        intake_motor = -70;
        pros::delay(100);
        intake_motor = 100
        pros::delay(350);
        numDisk--;
    }
}