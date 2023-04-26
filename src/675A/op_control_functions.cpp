#include "main.h"
using namespace pros;
void flywheel_toggle_function() {
  while (true) {
    if (master.get_digital_new_press(flywheel_toggle_button)) {
        is_flywheel_on = !is_flywheel_on;
    }
    delay(ez::util::DELAY_TIME);
  }
}
void speed_toggle_function() {
  while (true) {
    if (master.get_digital(speed_toggle_button)) {
      is_high_speed = true;
    } else {
      is_high_speed = false;
      disable_tongue_speed = false;
    }
    delay(ez::util::DELAY_TIME);
  }
}
void tongue_control_toggle_function() {
  while (true) {
    if (master.get_digital_new_press(tongue_toggle_button)) {
      if (is_tongue_up && !disable_tongue_speed) {
        is_tongue_up = !is_tongue_up;
        tongue_pneumatic.set_value(true);
      } else if (!is_tongue_up && !disable_tongue_speed) {
        is_tongue_up = !is_tongue_up;
        tongue_pneumatic.set_value(false);
      }
    }
    delay(ez::util::DELAY_TIME);
  }
}
void intake_control_toggle_function() {
  while (true) {
    if (master.get_digital(intake_in_button)) {
      is_outtaking = false;
      intake_power(intake_in_speed);
    } else if (master.get_digital(intake_out_button)) {
      is_outtaking = true;
      intake_power(intake_out_speed);
    } else {
      is_outtaking = true;
      intake_motor.move_velocity(0);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void speed_control() {
  while (true) {
    if (is_flywheel_on) {
      if (is_high_speed || !is_outtaking) {
        disable_tongue_speed = true;
        flywheel.set_mode(2);
      } else if (is_tongue_up) {
        flywheel.set_mode(1);
        flywheel.set_target(tongue_up_speed);
      } else if (!is_tongue_up) {
        flywheel.set_mode(1);
        flywheel.set_target(tongue_down_speed);
      } 
    } else {
      flywheel.set_mode(3);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void endgame_control_function() {
  while (true) {
    if (master.get_digital(expansion_toggle_button_1) &&
        master.get_digital(expansion_toggle_button_2)) {
      endgame_pneumatic.set_value(true);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void drive_lock_control_function() {
  while (true) {
    if (master.get_digital(drive_lock_toggle_button)) {
      if (drive_lock_toggle) {
        drive_lock_toggle = !drive_lock_toggle;
        drive_lock_type = "Hold ";
        chassis.set_drive_brake(E_MOTOR_BRAKE_HOLD);
        chassis.set_active_brake(0.1);
      } else {
        drive_lock_toggle = !drive_lock_toggle;
        drive_lock_type = "Coast";
        chassis.set_drive_brake(E_MOTOR_BRAKE_COAST);
        chassis.reset_drive_sensor();
        chassis.set_active_brake(0.0);
      }
    }
    delay(ez::util::DELAY_TIME);
  }
}
void set_speed_manually() {
  while (true) {
    double target = 1500;
    if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      target += 100;
      flywheel.set_mode(1);
      flywheel.set_target(target);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      target -= 100;
      flywheel.set_mode(1);
      flywheel.set_target(target);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      intake_power(100);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      intake_power(-100);
    } else {
      intake_motor.move_velocity(0);
      flywheel.set_mode(3);
    }
    delay(ez::util::DELAY_TIME);
  }
}