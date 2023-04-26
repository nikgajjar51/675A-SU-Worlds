#include "main.h"
using namespace pros;
int get_flywheel_temp() { return flywheel_motor.get_temperature(); }
int get_intake_temp() { return intake_motor.get_temperature(); }
double get_flywheel_velocity() { return flywheel_motor.get_actual_velocity(); }
void flywheel_power(double percent) { flywheel_motor.move(percent); }
void intake_power(double percent) { intake_motor.move_voltage(percent); }
void autonomous_data_export() {
  while (true) {
    master.print(0, 0, "Auto: %i", as::auton_selector.current_auton_page);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel_motor.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
void driver_data_export() {
  while (true) {
    master.print(0, 0, "Drive: %s", drive_lock_type);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel_motor.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}