#include "main.h"
using namespace pros;
void flywheel_control_function() {
  while (true) {
    if (master.get_digital_new_press(flywheel_toggle_button)) {
      is_flywheel_running = !is_flywheel_running;
    }
    delay(ez::util::DELAY_TIME);
  }
}
void tongue_control_function() {
  while (true) {
    if (master.get_digital_new_press(tongue_toggle_button)) {
      is_tongue_up = !is_tongue_up;
      if (is_tongue_up) {
        tongue_pneumatic.set_value(true);
        flywheel.set_target(tongue_up_speed);

      } else if (!is_tongue_up) {
        tongue_pneumatic.set_value(false);
        flywheel.set_target(tongue_down_speed);
      }
    }
    delay(ez::util::DELAY_TIME);
  }
}
void speed_control_function() {
  while (true) {
    if (master.get_digital_new_press(flywheel_toggle_button)) {
      if (!flywheel_toggle) {
        flywheel.set_mode(3);
        flywheel_toggle = true;
      } else {
        flywheel.set_mode(1);
        flywheel_toggle = false;
      }
    }
  }
  delay(ez::util::DELAY_TIME);
}

void intake_control_function() {
  while (true) {
    if (master.get_digital(intake_in_button)) {
      is_outtaking = false;
      intake_power(intake_in_speed);
    } else if (master.get_digital(intake_out_button)) {
      flywheel.set_mode(2);
      is_outtaking = true;
      intake_power(intake_out_speed);
    } else {
      if (master.get_digital(speed_toggle_button)) {
        flywheel.set_mode(2);
      } else {
        flywheel.set_mode(1);
      }
      is_outtaking = false;
      intake_motor.move_velocity(0);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void endgame_control_function() {
  while (true) {
    if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN) &&
        master.get_digital(E_CONTROLLER_DIGITAL_RIGHT) &&
        master.get_digital(E_CONTROLLER_DIGITAL_Y) &&
        master.get_digital(E_CONTROLLER_DIGITAL_B)) {
      endgame_pnematic.set_value(true);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void drive_lock_control_function() {
  if (master.get_digital(drive_lock_toggle_button)) {
    if (drive_lock_toggle) {
      drive_lock_toggle = !drive_lock_toggle;
      drive_lock_type = "Hold ";
      chassis.set_drive_brake(E_MOTOR_BRAKE_HOLD);
      chassis.set_active_brake(0.0);
    } else {
      drive_lock_toggle = !drive_lock_toggle;
      drive_lock_type = "Coast";
      chassis.set_drive_brake(E_MOTOR_BRAKE_COAST);
      chassis.reset_drive_sensor();
      chassis.set_active_brake(0.1);
    }
  }
}