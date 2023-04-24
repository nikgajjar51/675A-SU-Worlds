#include "api.h"
#pragma once
/**
 * @brief Drive Speed: Teh default drive forward and reverse speed in
 * autonomous.
 *
 */
extern const int drive_speed;
/**
 * @brief Turn Speed: The default turn speed in autonomous.
 *
 */
extern const int turn_speed;
/**
 * @brief Swerve Speed: The default swerve speed in autonomous.
 *
 */
extern const int swerve_speed;
/**
 * @brief Low Speed Multiplier: The low adjustment for slow movements.
 *
 */
extern const double low_speed_multiplier;
/**
 * @brief Normal Speed Multiplier: The normal adjustment for basic drive.
 * movements
 *
 */
extern const double normal_speed_multiplier;
/**
 * @brief High Speed Multiplier: The fast adjustment for basic drive movements.
 *
 */
extern const double high_speed_multiplier;
/**
 * @brief Balls to The Walls: The FASTEST adjustment for basic drive movements.
 *
 */
extern const double balls_to_the_walls;
/**
 * @brief The bang-bang speed for when the tongue is up.
 *
 */
extern double tongue_up_speed;
/**
 * @brief The bang-bang speed for when the tongue is down.
 *
 */
extern double tongue_down_speed;
/**
 * @brief Drive Lock Type: A string used to print the current drive brake mode
 * to the controller screen, if desired.
 *
 */
extern std::string drive_lock_type;
/**
 * @brief Alliance: A string used to print the current alliance color to the
 * controller scree, if desireed.
 *
 */
extern std::string alliance;

extern bool drive_lock_toggle;
extern bool intake_clamp_toggle;
extern bool flywheel_toggle;
extern bool intake_clamp_state;
extern bool is_flywheel_running;
extern bool is_tongue_up;
extern bool is_outtaking;
extern bool is_high_speed;
extern const double p_kP, p_kI, p_kD, p_kF;
extern double p_error, p_last_error, p_derivative, p_integral,
    p_currentVelocity, p_power;
extern double intake_in_speed, intake_out_speed;
void chassis_default_constants();
void chassis_exit_condition_defaults();
void chassis_modified_exit_condition();