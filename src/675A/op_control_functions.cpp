#include "main.h"
using namespace pros;
void flywheel_control_function() {
  while (true) {
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
      is_flywheel_running = !is_flywheel_running;
    }
    delay(ez::util::DELAY_TIME);
  }
}
void tongue_control_function() {
  while (true) {
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
      is_tongue_up = !is_tongue_up;
      if (is_tongue_up) {
        tongue_pneumatic.set_value(true);

      } else if (!is_tongue_up) {
        tongue_pneumatic.set_value(false);
      }
    }
    delay(ez::util::DELAY_TIME);
  }
}
void flywheel_function(double shooting_speed, double bang_bang_speed) {
  if (is_flywheel_running) {
    if (!is_outtaking) {
      bang_bang_control_function(bang_bang_speed); // Target Speed of Bang Bang
    } else if (is_outtaking) {
      flywheel.move_velocity(shooting_speed);
    }
  } else if (!is_flywheel_running) {
    flywheel.move_voltage(0);
  }
}
void intake_control_function() {
  while (true) {
    if (master.get_digital(intake_in_button)) {
      is_outtaking = false;
      intake_power(intake_in_speed);
    } else if (master.get_digital(intake_out_button)) {
      is_outtaking = true;
      intake_power(intake_out_speed);
    } else {
      is_outtaking = false;
      intake.move_velocity(0);
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