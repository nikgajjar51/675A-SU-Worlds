#include "constants.hpp"
#include "helper_functions.hpp"
#include "main.h"
#include "pros/rtos.hpp"
using namespace pros;
void drive_example()
{
  chassis.set_drive_pid(24, 110, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();
}
void right_side_1()
{
  // Start Flywheel
  flywheel.set_mode(1);
  flywheel.set_target(3400);
  pros::delay(500);
  // Go fwd
  chassis.set_drive_pid(13, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // Turn
  chassis.set_turn_pid(-18, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // Fire
  intake_power(12000);
  pros::delay(1000);
  intake_power(0);
  // Go to 0
  chassis.set_turn_pid(0, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // start intake disks
  intake_power(-12000);
  // go fwd to intake
  chassis.set_drive_pid(10, drive_speed * low_speed_multiplier);
  chassis.wait_drive();
  // wait to intake
  pros::delay(1500);
  // stop intake
  intake_power(0);
  // Turn
  chassis.set_turn_pid(-18, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // Fire
  intake_power(12000);
  pros::delay(1);
  intake_power(0);
  // Turn
  chassis.set_turn_pid(0, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_drive_pid(-32, drive_speed * normal_speed_multiplier); //-24
  chassis.wait_drive();
  intake_power(-6000);
  pros::delay(500);
  intake_power(0);
  pros::delay(500);
  /*
  chassis.set_turn_pid(45, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(-12000);
  chassis.set_drive_pid(50, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_drive_pid(24, drive_speed * low_speed_multiplier);
  chassis.wait_drive();
  pros::delay(1000);
  intake_power(0);
  chassis.set_turn_pid(-45, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_drive_pid(12, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // Fire
  for (int i = 0; i < 3; i++)
  {
    intake_power(6000);
    pros::delay(250);
    intake_power(0);
    pros::delay(250);
  }*/
}
void roller_only()
{
  chassis.set_drive_pid(-4, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(6000);
  pros::delay(500);
  intake_power(0);
  pros::delay(500);
}
void roller_only_2()
{
  flywheel.set_mode(1);
  flywheel.set_target(3400);
  chassis.set_drive_pid(-4, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(-12000);
  pros::delay(500);
  intake_power(0);
  pros::delay(500);
  chassis.set_drive_pid(18, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();


  chassis.set_turn_pid(-15, turn_speed * normal_speed_multiplier);
  chassis.wait_drive();
  pros::delay(200);
  intake_power(12000);
  flywheel.set_target(3500);


  pros::delay(100);
  intake_power(-6000);
  pros::delay(1350);
  intake_power(12000);
  pros::delay(100);
  intake_power(0);
  delay(500);
}
void left_side_1()
{
  // x, y
  //  3.5 ,36, 270
  flywheel.set_mode(1);
  flywheel.set_target(3000);
  intake_power(100);
  chassis.set_drive_pid(-1, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(0);
  // 2.5, 36, 270
  chassis.set_drive_pid(9.5, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 12, 36, 270
  chassis.set_turn_pid(-9.352, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 12, 36, 279.352
  flywheel.fire_discs(2);
  pros::delay(900);
  // preloads fire
  chassis.set_turn_pid(54.352, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 12, 36, 225
  chassis.set_drive_pid(16.97, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 24, 48, 225
  chassis.set_turn_pid(-90, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 24, 48, 315
  intake_power(-50);
  // intake 3 stack on line
  chassis.set_drive_pid(16.97, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 36, 36, 315
  pros::delay(1000);
  chassis.set_drive_pid(-8.485, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(0);
  // 30, 42, 315
  chassis.set_turn_pid(30.347, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 30, 42, 284.653
  flywheel.fire_discs(3);
  pros::delay(1350);
  // shoots 3 stack
  chassis.set_turn_pid(-30.347, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 30, 42, 315
  chassis.set_drive_pid(-8.485, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 24, 48, 315
  chassis.set_turn_pid(90, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 24, 48, 225;
  intake_power(-50);
  chassis.set_drive_pid(16.97, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  pros::delay(1000);
  // 36, 60, 225
  chassis.set_turn_pid(-70.983, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  // 36, 60, 295.983
  intake_power(0);
  pros::delay(300);
  flywheel.fire_discs(3);
  // shoot last 3
}
 void actual_right(){
   flywheel.set_mode(1);
  flywheel.set_target(3450);
  chassis.set_drive_pid(-37, drive_speed *normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_turn_pid(90, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(-6000);
  chassis.set_drive_pid(-6, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(0);
  chassis.set_drive_pid(20, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_turn_pid(95, drive_speed * normal_speed_multiplier);
  chassis.wait_drive();
  chassis.wait_drive();
  pros::delay(200);
  intake_power(12000);
  flywheel.set_target(3500);
  pros::delay(100);
  intake_power(-6000);
  pros::delay(1350);
  intake_power(12000);
  pros::delay(100);
  intake_power(0);
  pros::delay(500);
flywheel.set_target(3000);
  chassis.set_drive_pid(-12, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  chassis.set_turn_pid(42, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(-12000);
  chassis.set_drive_pid(100, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  /*chassis.move_voltage(-10000);
  pros::delay(1000);
  chassis.move_voltage(0);
  pros::delay(500);
  chassis.move(10000);
  pros::delay(1000);
  chassis.move_voltage(0);
  pros::delay(500);*/

  chassis.set_turn_pid(130, drive_speed*normal_speed_multiplier);
  chassis.wait_drive();
  intake_power(0);

  pros::delay(200);
  intake_power(12000);
  flywheel.set_target(3200);
  pros::delay(100);
  intake_power(-6000);
  pros::delay(1350);
  intake_power(12000);
  pros::delay(100);
  intake_power(0);
  pros::delay(100);
  intake_power(-6000);
  pros::delay(1350);
  intake_power(12000);
  pros::delay(100);
  intake_power(0);
  pros::delay(500);
 }