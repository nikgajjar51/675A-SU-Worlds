#pragma once
#include "api.h"
using namespace pros;
void flywheel_control_function();
void tongue_control_function();
void flywheel_function();
void speed_control_function();
void intake_clamp_control_function();
void intake_control_function();
void endgame_control_function();
void drive_lock_control_function();
extern Task autonomous_data_export_task;
extern Task drive_data_export_task;
extern Task flywheek_task;
extern Task tongue_task;
extern Task intake_task;
extern Task endgame_task;
extern Task speed_task;