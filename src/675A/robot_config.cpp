#include "main.h"
using namespace pros;

pros::Motor flywheel(7, pros::E_MOTOR_GEARSET_06, true,
                     pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(1, pros::E_MOTOR_GEARSET_06, true,
                   pros::E_MOTOR_ENCODER_DEGREES);
pros::ADIAnalogOut intake_pneumatic('A');
pros::ADIAnalogOut endgame_pnematic('B');
pros::ADIAnalogOut tongue_pneumatic('C');