#include "api.h"
#pragma once
using namespace pros;
class flywheel_controller {
public:
  void set_target(double target_speed);
  void set_mode(int mode);
  void fly_control();
  void fire_discs(int numDisk, int fireTime);

private:
  pros::Mutex flywheel_rpm_guard;
  pros::Mutex flywheel_mode_guard;
  double flywheel_target_rpm = 2600;
  int mode_ = 3;
};
extern flywheel_controller flywheel;