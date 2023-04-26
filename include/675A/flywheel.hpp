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
  void lock_flywheel();
  bool get_lock();
  double get_target_speed();
  double get_flywheel_velocity();
  int get_mode();
  void jank_fire(double target, int mode);
  bool is_flywheel_running;
  bool flywheel_state;
  bool flywheel_locked = false;

private:
  void wait_until(int maxHold);
  Mutex flywheel_rpm_guard;
  Mutex flywheel_mode_guard;
  Mutex flywheel_get_rpm_guard;
  Mutex flywheel_get_target_guard;
  Mutex flywheel_get_mode_guard;
  Mutex flywheel_lock_guard;
  Mutex flywheel_get_lock_guard;
  double flywheel_target_rpm = 2600;
  int mode_ = 3;
};
extern flywheel_controller flywheel;