#include "main.h"
using namespace pros;
const int drive_speed = 70, turn_speed = 75, swerve_speed = 50;
const double low_speed_multiplier = .5, normal_speed_multiplier = 1,
             high_speed_multiplier = 1.7, balls_to_the_walls = 2;
double shooting_speed_high, shooting_speed_low, shooting_speed,
    bang_bang_speed;
std::string drive_lock_type = "Coast", alliance = "Red";
bool drive_lock_toggle = false, intake_clamp_toggle = true,
     intake_clamp_state = true, is_flywheel_running = false,
     is_tongue_up = false, is_outtaking = false, is_high_speed = false;
void chassis_default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 12, 0, 40, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}
void chassis_exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}
void chassis_modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

// FeedForward Constants
const double kP = 1.2;
const double kF = 1.2;
double error, lastError, derivative, integral, currentVelocity, power;

// Old PID  Constants
const double p_kP = 1.2;
const double p_kI = .1;
const double p_kD = .7;
const double p_kF = 0; // was 1.2
double p_error, p_last_error, p_derivative, p_integral, p_currentVelocity,
    p_power;
// Motor Constants
double intake_in_speed = 127;
double intake_out_speed = -127;