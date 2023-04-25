#include "main.h"
using namespace pros;
int get_flywheel_temp() { return flywheel_motor.get_temperature(); }
int get_intake_temp() { return intake_motor.get_temperature(); }
double get_flywheel_velocity() { return flywheel_motor.get_actual_velocity(); }
void flywheel_power(double percent) { flywheel_motor.move(percent); }
void intake_power(double percent) { intake_motor.move_voltage(percent); }
void pid_control_function_2(double target_speed) {
  p_currentVelocity = get_flywheel_velocity();
  p_error = target_speed - p_currentVelocity;
  p_derivative = p_error - p_last_error;
  p_integral = p_integral + p_error;
  p_power = (p_kP * p_error) + (p_kI * p_integral) + (p_kD * p_derivative) +
            (target_speed * p_kF);
  flywheel_motor.move_voltage(p_power);
  std::cout << p_power << std::endl;
  p_last_error = p_error;
}
void autonomous_data_export() {
  while (true) {
    master.print(0, 0, "Auto: %i", as::auton_selector.current_auton_page);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel_motor.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
void driver_data_export() {
  while (true) {
    master.print(0, 0, "Drive: %s", drive_lock_type);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel_motor.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
bool assign_multiple_buttons(
    std::vector<pros::controller_digital_e_t> input_buttons) {
  for (int i; i <= input_buttons.size(); i++) {
    return master.get_digital(input_buttons.at(i));
  }
  return false;
}