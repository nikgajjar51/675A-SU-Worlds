#include "main.h"
using namespace pros;
std::string drive_lock_type = "Coast", alliance = "Red", intake_clamp_position;
bool drive_lock_toggle = false, intake_clamp_toggle = false,
     intake_clamp_state = true, is_flywheel_running = false,
     is_tongue_up = true;
controller_digital_e_t flywheel_toggle_button = E_CONTROLLER_DIGITAL_R2;
controller_digital_e_t tongue_toggle_button = E_CONTROLLER_DIGITAL_LEFT;
controller_digital_e_t tongue_speed_button = E_CONTROLLER_DIGITAL_UP;
controller_digital_e_t intake_clamp_toggle_button = E_CONTROLLER_DIGITAL_R1;
controller_digital_e_t intake_in_button = E_CONTROLLER_DIGITAL_L1;
controller_digital_e_t intake_out_button = E_CONTROLLER_DIGITAL_L2;
controller_digital_e_t drive_lock_toggle_button = E_CONTROLLER_DIGITAL_RIGHT;
void flywheel_control_function() {
  if (master.get_digital(flywheel_toggle_button)) {
    is_flywheel_running = !is_flywheel_running;
    flywheel_integral = 0;
    for (int i = 0; i < flywheel_smooth_size; i++) {
      flywheel_speeds[i] = 0;
    }
    std::cout << endl << endl << "new power:" << endl << endl;
  }
}
void tongue_control_function() {
  while (true) {
    if (master.get_digital(tongue_toggle_button)) {
      is_tongue_up = !is_tongue_up;
    }
    if (is_flywheel_running) {
      flywheel_pid(7600);
      if (is_tongue_up) {
        tongue_pneumatic.set_value(false);
      } else {
        tongue_pneumatic.set_value(true);
      }
    } else {
      flywheel_power(0);
    }
    delay(ez::util::DELAY_TIME);
  }
}
void intake_clamp_control_function() {
  if (master.get_digital(intake_clamp_toggle_button)) {
    if (intake_clamp_toggle) {
      intake_clamp_state = !intake_clamp_state;
      intake_clamp_position = "In ";
    } else if (intake_clamp_toggle) {
      intake_clamp_state = !intake_clamp_state;
      intake_clamp_position = "Out";
    }
  }
}
void intake_control_function() {
  while (true) {
    if (master.get_digital(intake_in_button)) {
      intake_power(intake_in_speed);
      intake_pneumatic.set_value(intake_clamp_state);
    } else if (master.get_digital(intake_out_button)) {
      intake_power(intake_out_speed);
      intake_pneumatic.set_value(intake_clamp_state);
    } else {
      intake.move_velocity(0);
      intake_pneumatic.set_value(false);
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