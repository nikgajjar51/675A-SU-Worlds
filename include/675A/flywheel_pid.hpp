#pragma once
#include "api.h"
using namespace pros;
class FlywheelController {
public:
  FlywheelController(double kp, double ki, double kd, double ff_gain,
                     double flywheel_inertia) {
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
    ff_gain_ = ff_gain;
    flywheel_inertia_ = flywheel_inertia;
    last_error_ = 0;
    integral_error_ = 0;
  }

  double compute(double setpoint, double feedback, double power_input,
                 double dt) {
    double speed_error = setpoint - feedback;
    integral_error_ += speed_error * dt;
    double derivative_error = (speed_error - last_error_) / dt;
    last_error_ = speed_error;
    double predicted_speed_change = power_input / flywheel_inertia_ * dt;
    double feedforward_output = ff_gain_ * predicted_speed_change;
    double pid_output =
        kp_ * speed_error + ki_ * integral_error_ + kd_ * derivative_error;
    return feedforward_output + pid_output;
  }

private:
  double kp_;
  double ki_;
  double kd_;
  double ff_gain_;
  double flywheel_inertia_;
  double last_error_;
  double integral_error_;
};
