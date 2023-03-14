#pragma once
#include "api.h"
extern int get_flywheel_temp();
extern int get_intake_temp();
extern double get_flywheel_velocity();
void flywheel_power(double percent);
void intake_power(double percent);
extern double mean(double x, double y);
extern double clamp(double val, double max, double min);
extern int constrain(int value, int min, int max);
extern double flywheel_get_velocity();
void flywheel_feedforward_pid(double target_speed);
void flywheel_pid(double target_speed);