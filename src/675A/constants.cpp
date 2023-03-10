#include "main.h"
using namespace pros;
const int drive_speed = 70, turn_speed = 75, swerve_speed = 50;
const double low_speed_multiplier = .5, normal_speed_multiplier = 1,
             high_speed_multiplier = 1.7, balls_to_the_walls = 2;
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

// PID Constants
#define flywheel_smooth_size 3
#define flywheel_integral_smoothing 2
double flywheel_speeds[flywheel_smooth_size];
double flywheel_kP = 1.0;
double flywheel_kI = (1.0 / flywheel_integral_smoothing);
double flywheel_integral = 0;
double flywheel_error = 0;
double flywheel_speed = 0;
double flywheel_current_velocity = 0;

// FeedForward Constants
double kP = 0.1;
double kI = 0.0;
double kD = 0.0;
double kF = 0.1;

double error, integral, derivative, lastError;
double lastTime, deltaTime;

// Motor Constants
double intake_in_speed = 100;
double intake_out_speed = 33;