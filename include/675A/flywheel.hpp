#include "api.h"
#pragma once
using namespace pros;
class flywheel_controller {
public:
  void set_target(double target_speed);
  void set_mode(int mode);
  void fly_control();

private:
  Mutex flywheel_rpm_guard, flywheel_mode_guard;
  double flywheel_target_rpm;
  int mode_;
};
extern flywheel_controller flywheel;