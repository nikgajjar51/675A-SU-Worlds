#pragma once
#include "api.h"
using namespace pros;
extern Motor flywheel;
extern Motor intake;
extern ADIAnalogOut intake_pneumatic;
extern ADIAnalogOut endgame_pnematic;
extern ADIAnalogOut tongue_pneumatic;
extern controller_digital_e_t flywheel_toggle_button;
extern controller_digital_e_t tongue_toggle_button;
extern controller_digital_e_t intake_clamp_toggle_button;
extern controller_digital_e_t intake_in_button;
extern controller_digital_e_t intake_out_button;
extern controller_digital_e_t drive_lock_toggle_button;