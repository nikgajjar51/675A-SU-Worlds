#include "constants.hpp"
#include "main.h"
#include "robot_config.hpp"
using namespace pros;
void flywheel_control_function() {
  while (true) {
  }
  if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
    is_flywheel_running = !is_flywheel_running;
  }
  if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
    is_tongue_up = !is_tongue_up;
  }
  if (is_flywheel_running) {
    if (is_tongue_up) {
      tongue_pneumatic.set_value(true);
      // feedforward_control_function(425);
      // pid_control_function_2(425); // OLD PID
      bang_bang_control_function(2000); // Target Speed out of 3600

    } else {
      tongue_pneumatic.set_value(false);
      // feedforward_control_function(550);
      // pid_control_function_2(550); // OLD PID
      bang_bang_control_function(3300); // Target Speed out of 3600
    }
  } else if (!is_flywheel_running) {
    flywheel.move_voltage(0);
  }
}
void intake_control_function() {
  while (true) {
    if (master.get_digital(intake_in_button)) {
      intake_power(intake_in_speed);
    } else if (master.get_digital(intake_out_button)) {
      if(is_flywheel_running){
        flywheel.move_voltage(12000); // flywheel Shoots when intaking
      }
      intake_power(intake_out_speed);
    } else {
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