/**
 * @file flywheel.hpp
 * @author Nikhil Gajjar
 * @brief Flywheel control class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "api.h"
#pragma once
using namespace pros;
class flywheel_controller {
public:
  void set_target(double target_speed);
  void set_mode(int mode);
  void fly_control();
  void fire_discs(int numDisk);

private:
  Mutex flywheel_rpm_guard;
  Mutex flywheel_mode_guard;
  double flywheel_target_rpm = 2600;
  int mode_ = 3;
};
extern flywheel_controller flywheel;