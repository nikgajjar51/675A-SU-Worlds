#include "main.h"
using namespace pros;
void flywheel_controller::set_target(double target_speed) {
  flywheel_rpm_guard.take();
  if (get_lock() == false) {
    flywheel_target_rpm = (double)target_speed;
  }
  flywheel_rpm_guard.give();
}

int flywheel_controller::get_mode() {
  flywheel_get_mode_guard.take();
  int return_val = (int)mode_;
  flywheel_get_mode_guard.give();
  return return_val;
}

double flywheel_controller::get_flywheel_velocity() {
  return (double)flywheel_motor.get_actual_velocity();
}

double flywheel_controller::get_target_speed() {
  flywheel_get_target_guard.take();
  double return_val = (double)flywheel_target_rpm;
  flywheel_get_target_guard.give();
  return return_val;
}

void flywheel_controller::set_mode(int mode) {
  flywheel_mode_guard.take();
  if (get_lock() == false) {
    mode_ = mode;
  }
  flywheel_mode_guard.give();
}

void flywheel_controller::lock_flywheel() {
  flywheel_lock_guard.take();
  flywheel_locked = !flywheel_locked;
  flywheel_lock_guard.give();
}

bool flywheel_controller::get_lock() {
  flywheel_get_lock_guard.take();
  bool return_val = (bool)flywheel_locked;
  flywheel_get_lock_guard.give();
  return return_val;
}

void flywheel_controller::fly_control() {
  uint32_t t = pros::millis();

  while (true) {
    int mode = get_mode();
    if (mode == 1) {
      if ((get_flywheel_velocity() * 6) < get_target_speed()) {
        flywheel_motor.move_voltage(12000);
      } else {
        flywheel_motor.move_voltage((get_target_speed() / 3600) * 12000);
      }
    } else if (mode == 2) {
      flywheel_motor.move_voltage(12000);
    } else if (mode == 3) {
      flywheel_motor.move_voltage(0);
    }

    pros::Task::delay_until(&t, 10);
  }
}

void flywheel_controller::wait_until(int maxHold) {
  int time = 0;
  while (get_target_speed() > (get_flywheel_velocity() * 6) && time < maxHold) {
    pros::delay(10);
    time += 10;
  }
}

void flywheel_controller::fire_discs(int numDisk) {
  set_mode(1);

  for (int i = 0; i < numDisk; i++) {
    intake_motor = 80;
    pros::delay(100);
    intake_motor = -127;
    pros::delay(300);
    wait_until(100);
  }
  intake_motor = 0;
}

void flywheel_controller::jank_fire(double target, int mode, int numDisk) {
  mode_ = mode;
  flywheel_target_rpm = target;

  pros::delay(2000);
  fire_discs(numDisk);
}