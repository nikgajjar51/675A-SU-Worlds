#pragma once
#include "api.h"
using namespace pros;
extern double mean(double x, double y);
extern double clamp(double val, double max, double min);
extern int constrain(int value, int min, int max);
extern double flywheel_get_velocity();
extern void flywheel_pid(double target_speed);
extern void flywheel_async_pid_control(double target_speed);