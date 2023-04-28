#include "api.h"
#pragma once
extern const int drive_speed, turn_speed, swerve_speed;
extern const double low_speed_multiplier, normal_speed_multiplier,
    high_speed_multiplier, balls_to_the_walls;
extern double tongue_up_speed, tongue_down_speed;
extern std::string drive_lock_type;
extern std::string alliance;
extern bool drive_lock_toggle, is_flywheel_on, is_tongue_up, is_outtaking,
    is_high_speed, disable_tongue_speed;
extern double intake_in_speed, intake_out_speed;
void chassis_default_constants();
void chassis_exit_condition_defaults();
void chassis_modified_exit_condition();