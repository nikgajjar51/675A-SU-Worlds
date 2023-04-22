#include "main.h"
#include "robot_config.hpp"
using namespace pros;
int get_flywheel_temp() { return flywheel.get_temperature(); }
int get_intake_temp() { return intake.get_temperature(); }
double get_flywheel_velocity() { return flywheel.get_actual_velocity(); }
void flywheel_power(double percent) { flywheel.move(120 * percent); }
void intake_power(double percent) { intake.move(120 * percent); }
void feedforward_control_function(double target_speed) {
  currentVelocity = get_flywheel_velocity();
  error = target_speed - currentVelocity;
  power = (kP * error) + (target_speed * kF);
  flywheel.move_voltage(power);
  std::cout << power << std::endl;
  lastError = error;
}
void pid_control_function_2(double target_speed) {
  p_currentVelocity = get_flywheel_velocity();
  p_error = target_speed - p_currentVelocity;
  p_derivative = p_error - p_last_error;
  p_integral = p_integral + p_error;
  p_power = (p_kP * p_error) + (p_kI * p_integral) + (p_kD * p_derivative) +
            (target_speed * p_kF);
  flywheel.move_voltage(p_power);
  std::cout << p_power << std::endl;
  p_last_error = p_error;
}
void bang_bang_control_function(double target_speed) {
  if (get_flywheel_velocity() < target_speed) {
    flywheel.move_voltage(12000);
  } else {
    flywheel.move_voltage((target_speed / 3600) * 12000);
  }
}
void autonomous_data_export() {
  while (true) {
    master.print(0, 0, "Alliance: %s", alliance);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel.get_actual_velocity() / 10) * 60);
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
                 abs(flywheel.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
