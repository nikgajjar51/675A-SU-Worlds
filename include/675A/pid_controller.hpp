#include "api.h"
#pragma once
using namespace pros;
class FAPID {
public:
  FAPID();
  FAPID(double kF, double kA, double kP, double kI, double kD, double start_kI,
        std::string name = "");
  struct Gains {
    double kF;
    double kA;
    double kP;
    double kI;
    double kD;
    double start_kI;
  };
  Gains gains;
  Gains get_gains();
  void set_gains(double kF, double kA, double kP, double kI, double kD,
                 double start_kI);
  void set_target(double input_target);
  void set_sensor();
  double compute_target(double sensor);
  void set_name(std::string name);
  void reset_variables();
  double get_target();
  double change;
  double derivative;
  double integral;
  double error;
  double previous_error;
  double previous_output;
  double target;
  double output;
};