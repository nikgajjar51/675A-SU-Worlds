#pragma once
#include "api.h"

extern const int drive_speed, turn_speed, swerve_speed;
extern const double low_speed_multiplier, normal_speed_multiplier,
    high_speed_multiplier, balls_to_the_walls;

// Robot Constants and Toggles
extern std::string drive_lock_type, alliance, intake_clamp_position;
extern bool drive_lock_toggle, intake_clamp_toggle, intake_clamp_state,
    is_flywheel_running, is_tongue_up, is_outtaking;
// Chassis PID's
void chassis_default_constants();
void chassis_exit_condition_defaults();
void chassis_modified_exit_condition();

// Feed Forward Constants
extern const double kP, kF;
extern double error, lastError, derivative, integral, currentVelocity, power;

// Old Feed Forward Constants
extern const double p_kP, p_kI, p_kD, p_kF;
extern double p_error, p_last_error, p_derivative, p_integral, p_currentVelocity, p_power;

// Motor Constants
extern double intake_in_speed, intake_out_speed;