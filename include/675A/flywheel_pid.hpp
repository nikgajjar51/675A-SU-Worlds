#pragma once

struct flywheel_pid_settings {
  double kP;  // P controller constant
  double kI;  // I controller constant
  double kD;  // V controller constant
  double kF; // FF controller constant, Airplane for control surface control,
             // use instead of D (V)
  double outLimits; // output limits
  double dFilter;   // IIR filter for D part, start with 0 and increase during
                   // testing
  double accLimit;  // a separate limit for the Integral part, start with 1 and
                   // decrease during testing
};

class flywheel_pid {
private:
  // variables used for setting up the PID loop
  double _kP;
  double _kI;
  double _kD;
  double _kF;

  double _outLimits;
  double _dFilter;
  double _accLimit;

  bool _enable;

  // internally used variables
  double _prevInput;
  double _accumulator;
  double _dBuffer;
  bool _resetState;

public:
  flywheel_pid()
      : _kP(0), _kI(0), _kD(0), _kF(0), _outLimits(1), _dFilter(0),
        _accLimit(1), _enable(false), _prevInput(0), _accumulator(0),
        _dBuffer(0), _resetState(true) {}

  void init(flywheel_pid_settings flywheel_pid_settings);
  void init(double kP, double kI, double kD, double kFF, double outLimits,
            double dFilter, double accLimit);
  flywheel_pid_settings get_flywheel_pid_settings();

  // run the calculations and return new output value
  // the spin function should be called at a stable frequency
  double set_velocity(double target_velocity);
  double set_velocity(double target_velocity, double attenuation);

  // commands for modifying coefficients on the fly
  void setKp(double kP);
  void setKi(double kI);
  void setKd(double kD);
  void setKf(double kFF);

  // enable or disable PID
  void enable();
  void disable();
  void reset();

  // read coefficients
  double getKp();
  double getKi();
  double getKd();
  double getKf();
};