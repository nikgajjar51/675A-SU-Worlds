#include "main.h"
using namespace pros;
void drive_example() {
  chassis.set_drive_pid(24, 110, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();
}
void right_side_1() {
  intake_power(-100);
  chassis.set_drive_pid(45, drive_speed * high_speed_multiplier);
  chassis.wait_drive();
  chassis.set_turn_pid(15, turn_speed * high_speed_multiplier);
  chassis.wait_drive();
  flywheel_power(100);
  delay(200);
  intake_power(20);
  delay(2000);
  intake_power(0);
  flywheel_power(0);
  chassis.set_turn_pid(-45, turn_speed * high_speed_multiplier);
  chassis.wait_drive();
  intake_power(-100);
  chassis.set_drive_pid(55, drive_speed * high_speed_multiplier);
  chassis.wait_drive();
  
}
