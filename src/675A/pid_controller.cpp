#include "pid_controller.hpp"
#include "main.h"

void FAPID::reset_variables() {
  change = 0;
  derivative = 0;
  integral = 0;
  error = 0;
  previous_error = 0;
  previous_output = 0;
  target = 0;
  output = 0;
}
FAPID::FAPID() {
  reset_variables();
  set_gains(0, 0, 0, 0, 0, 0);
}
FAPID::Gains FAPID::get_gains() { return gains; }
FAPID::FAPID(double kF_, double kA_, double kP_, double kI_, double kD_,
             double start_kI_, std::string name) {
  reset_variables();
  set_gains(kF_, kA_, kP_, kI_, kD_, start_kI_);
  set_name(name);
}
void FAPID::set_gains(double kF_, double kA_, double kP_, double kI_,
                      double kD_, double start_kI_) {
  gains.kF = kF_;
  gains.kA = kA_;
  gains.kP = kP_;
  gains.kI = kI_;
  gains.kD = kD_;
  gains.start_kI = start_kI_;
}
void FAPID::set_target(double input_target) { target = input_target; }
double FAPID::get_target() { return target; }
double FAPID::compute_target(double sensor) {
  error = target - sensor;
  derivative = error - previous_error;
  if (gains.kI != 0) {
    if (fabs(error) < gains.start_kI)
      integral += error;

    if (util::sgn(error) != util::sgn(previous_error))
      integral = 0;
  }
  output = (target * gains.kF) + (error * gains.kP) + (integral * gains.kI) +
           (derivative * gains.kD);
  if (gains.kA != 0) {
    change = output - previous_output;
    if (gains.kA == 0) {
      return output;
    }
    if (change > gains.kA) {
      change = gains.kA;
    } else if (change < -gains.kA) {
      change = -gains.kA;
    }
    return previous_output + change;
  }
  previous_output = output;
  previous_error = error;
  return output;
}