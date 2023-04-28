#include "main.h"
using namespace pros;
void programming_skills_1(void) {
    right_side_1();
    chassis.set_turn_pid(45, turn_speed * normal_speed_multiplier);
    chassis.wait_drive();
    chassis.set_drive_pid(-60, turn_speed * normal_speed_multiplier);
    chassis.wait_drive();
    endgame_pneumatic.set_value(false);
}