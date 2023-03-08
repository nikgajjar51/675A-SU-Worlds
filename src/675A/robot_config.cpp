#include "main.h"
using namespace pros;

pros::Motor flywheel(1, pros::E_MOTOR_GEARSET_06, true,
                     pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(2, pros::E_MOTOR_GEARSET_06, true,
                   pros::E_MOTOR_ENCODER_DEGREES);