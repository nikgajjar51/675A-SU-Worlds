#pragma once
#include "api.h"
using namespace pros;
extern Motor flywheel_motor;
extern Motor intake_motor;
extern ADIDigitalOut intake_pneumatic;
extern ADIDigitalOut endgame_pnematic;
extern ADIDigitalOut tongue_pneumatic;
extern controller_digital_e_t flywheel_toggle_button;
extern controller_digital_e_t tongue_toggle_button;
extern controller_digital_e_t speed_toggle_button;
extern controller_digital_e_t intake_in_button;
extern controller_digital_e_t intake_out_button;
extern controller_digital_e_t drive_lock_toggle_button;