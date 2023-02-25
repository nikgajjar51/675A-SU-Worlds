#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/rtos.hpp"
using namespace pros;
int get_flywheel_temp() { return flywheel.get_temperature(); }
//  int get_intake_temp() { return intake.get_temperature(); }
void flywheel_power(double percent) { flywheel.move(120 * percent); }
//  void intake_power(double percent) { intake.move(120 * percent); }
double mean(double x, double y) { return ((x + y) / 2); }
double clamp(double val, double max, double min) {
  return (std::max(std::min(val, max), min));
}
int constrain(int value, int min, int max) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}
double flywheel_get_velocity() {
  double sum = 0;
  for (int i = 0; i < flywheel_smooth_size; i++) {
    sum += flywheel_speeds[i];
  }
  return sum / flywheel_smooth_size;
}

void flywheel_feedforward_pid(double target_speed) {}
void flywheel_pid(double target_speed) {
  double current_velocity = (flywheel_get_velocity() * 36);
  flywheel_error = target_speed - current_velocity;
  for (int i = 0; i < flywheel_smooth_size - 1; i++) {
    flywheel_speeds[i] = flywheel_speeds[i - 1];
  }
  flywheel_speeds[flywheel_smooth_size - 1] = mean(
      abs(flywheel.get_actual_velocity()), abs(flywheel.get_actual_velocity()));
  flywheel_integral = clamp(flywheel_integral + ez::util::sgn(flywheel_error),
                            10 * flywheel_integral_smoothing,
                            -10 * flywheel_integral_smoothing);
  if (abs(flywheel_error) > 200) {
    flywheel_integral = 0;
  }
  flywheel_speed = clamp(
      flywheel_kP * flywheel_error + flywheel_kI * flywheel_integral, 100, 0);
  flywheel_power(flywheel_speed);
}

void flywheel_pid_2(double target_speed) {
  double error, integral, derivative, previous_error, kP, kI, kD;
  // Get the current velocity and rotation of the flywheel
  double current_velocity = flywheel.get_actual_velocity();
  double current_rotation = flywheel.get_position();

  // Calculate the error between the current speed and the target speed
  error = target_speed - current_velocity;

  // Calculate the integral term using the accumulated error
  integral += error;

  // Calculate the derivative term using the change in error
  derivative = error - previous_error;
  previous_error = error;

  // Calculate the output voltage using the PID constants and error terms
  double output_voltage = kP * error + kI * integral + kD * derivative;

  // Constrain the output voltage to the range (-127, 127)
  output_voltage = constrain(output_voltage, -127, 127);

  // Set the flywheel motor's voltage using the calculated output voltage
  flywheel.move(output_voltage);
}

void flywheel_pid_3(int target_speed) {
  double error, setpoint, integral, derivative, prevError, power, kI, kD, kP,
      range;
  error = setpoint - flywheel.get_actual_velocity();
  integral = integral + error;
  if (error == 0 || error > setpoint)
    integral = 0;
  if (error > range)
    integral = 0;
  derivative = error - prevError;
  prevError = error;
  power = error * kP + integral * kI + derivative * kD;
  pros::delay(util::DELAY_TIME);
}