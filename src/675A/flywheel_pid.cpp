#include "main.h"
using namespace pros;
double error, prevError, derivative, integral;
int motorPower;

void flywheel_feedforward_pid(double target_velocity) {
  error = target_velocity - get_flywheel_velocity();
  derivative = error - prevError;
  integral += error;
  motorPower = (kP * error) + (kI * integral) + (kD * derivative) +
               (kF * target_velocity);
  flywheel.move_voltage(motorPower);
  prevError = error;
}