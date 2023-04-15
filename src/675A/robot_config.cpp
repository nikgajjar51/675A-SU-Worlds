#include "main.h"
#include "pros/adi.hpp"
using namespace pros;
Motor flywheel(10, E_MOTOR_GEARSET_06, true,
                     E_MOTOR_ENCODER_DEGREES);
Motor intake(1, E_MOTOR_GEARSET_06, false,
                   E_MOTOR_ENCODER_DEGREES);
ADIDigitalOut intake_pneumatic('A');
ADIDigitalOut endgame_pnematic('B');
ADIDigitalOut tongue_pneumatic('H');
controller_digital_e_t flywheel_toggle_button = E_CONTROLLER_DIGITAL_B;
controller_digital_e_t tongue_toggle_button = E_CONTROLLER_DIGITAL_R1;
controller_digital_e_t intake_clamp_toggle_button = E_CONTROLLER_DIGITAL_R1;
controller_digital_e_t intake_in_button = E_CONTROLLER_DIGITAL_L1;
controller_digital_e_t intake_out_button = E_CONTROLLER_DIGITAL_L2;
controller_digital_e_t drive_lock_toggle_button = E_CONTROLLER_DIGITAL_RIGHT;