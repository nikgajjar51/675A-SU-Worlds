#pragma once
#include "api.h"

extern const int DRIVE_SPEED, TURN_SPEED, SWING_SPEED;
void chassis_default_constants();
void chassis_exit_condition_defaults();
void chassis_modified_exit_condition();
#define flywheel_smooth_size 3
#define flywheel_integral_smoothing 2
extern double flywheel_speeds[flywheel_smooth_size], flywheel_kP, flywheel_kI,
    flywheel_integral, flywheel_error, flywheel_speed,
    flywheel_current_velocity;

// FeedForward Constants
extern double kP, kI, kD, kF, error, integral, derivative, lastError, lastTime,
    deltaTime;