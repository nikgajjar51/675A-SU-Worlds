#pragma once
#include "api.h"
using namespace pros;
extern std::string drive_lock_type, alliance, intake_clamp_position;
extern bool drive_lock_toggle, intake_clamp_toggle, intake_clamp_state,
    is_flywheel_running, is_tongue_up;
extern controller_digital_e_t flywheel_toggle_button;
extern controller_digital_e_t tongue_toggle_button;
extern controller_digital_e_t tongue_speed_button;
extern controller_digital_e_t intake_clamp_toggle_button;
extern controller_digital_e_t intake_in_button;
extern controller_digital_e_t intake_out_button;
extern controller_digital_e_t drive_lock_toggle_button;
void flywheel_control_function(void *);
void tongue_control_function(void *);
void intake_clamp_control_function(void *);
void intake_control_function(void *);
void endgame_control_function(void *);
void drive_lock_control_function(void *);