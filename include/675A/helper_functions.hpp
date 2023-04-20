#pragma once
#include "api.h"
using namespace pros;
extern int get_flywheel_temp();
extern int get_intake_temp();
extern double get_flywheel_velocity();
void flywheel_power(double percent);
void intake_power(double percent);
void feedforward_control_function(double target_speed);
void autonomous_data_export();
void driver_data_export();