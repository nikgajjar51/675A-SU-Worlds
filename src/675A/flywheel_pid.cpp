#include "main.h"
using namespace pros;

#define PID_SCALE 100

void flywheel_pid::init(flywheel_pid_settings pidSettings) {
  setKp(pidSettings.kP);
  setKi(pidSettings.kI);
  setKd(pidSettings.kD);
  setKf(pidSettings.kF);
  _outLimits = pidSettings.outLimits;
  _dFilter = pidSettings.dFilter;
  _accLimit = pidSettings.accLimit * PID_SCALE;
  reset();
}

void flywheel_pid::init(double kP, double kI, double kD, double kF, double outLimits,
                        double dFilter, double accLimit) {
  setKp(kP);
  setKi(kI);
  setKd(kD);
  setKf(kF);
  _outLimits = outLimits;
  _dFilter = dFilter;
  accLimit = accLimit * PID_SCALE;
  reset();
}

flywheel_pid_settings flywheel_pid::get_flywheel_pid_settings() {
  flywheel_pid_settings pidSettings;
  pidSettings.kP = getKp();
  pidSettings.kI = getKi();
  pidSettings.kD = getKd();
  pidSettings.kF = getKf();
  pidSettings.outLimits = _outLimits;
  pidSettings.dFilter = _dFilter;
  pidSettings.accLimit = _accLimit;
  return pidSettings;
}

double flywheel_pid::set_velocity(double target_velocity) {
  return set_velocity(target_velocity, 1);
}

double flywheel_pid::set_velocity(double target_velocity, double attenuation) {

  double output = 0;
  double pControl = 0;
  double iControl = 0;
  double dControl = 0;
  double ffControl = 0;

  if (_enable) {

    if (_resetState) {
      _prevInput = get_flywheel_velocity();
      _resetState = false;
    }
    // Error
    double error = target_velocity - get_flywheel_velocity();

    // Proportional
    pControl = error * _kP * attenuation;

    // Intergral Accumulator + Accumulator Limiting
    if (_kI != 0) {

      _accumulator += error;
      if (_accumulator * _kI * attenuation > _outLimits * _accLimit) {
        _accumulator = _outLimits * _accLimit / (_kI * attenuation);
      } else if (_accumulator * _kI * attenuation < (-_outLimits * _accLimit)) {
        _accumulator = -(_outLimits * _accLimit / (_kI * attenuation));
      }

      iControl = _accumulator * _kI * attenuation;

    } else {

      _accumulator = 0;
      iControl = 0;
    }

    // Derivative
    if (_kD != 0) {

      _dBuffer =
          _dBuffer + (((get_flywheel_velocity() - _prevInput) - _dBuffer) / (_dFilter + 1));

      dControl = _dBuffer * _kD * attenuation;

    } else {
      _dBuffer = 0;
      dControl = 0;
    }

    // Feed Forward Control
    ffControl = target_velocity * _kF * attenuation;

    output = (pControl + iControl + dControl + ffControl) / PID_SCALE;

    _prevInput = get_flywheel_velocity();

    // Output Limiter
    if (output > _outLimits) {
      output = _outLimits;
    } else if (output < -(_outLimits)) {
      output = -(_outLimits);
    }

  } else {
    _accumulator = 0;
    _dBuffer = 0;
    output = 0;
  }

  return output;
}

void flywheel_pid::setKp(double kP) { _kP = kP; }
void flywheel_pid::setKi(double kI) { _kI = kI; }
void flywheel_pid::setKd(double kD) { _kD = kD; }
void flywheel_pid::setKf(double kF) { _kF = kF; }

void flywheel_pid::enable() { _enable = true; }
void flywheel_pid::disable() {
  _enable = false;
  reset();
}

void flywheel_pid::reset() {
  _prevInput = 0;
  _accumulator = 0;
  _dBuffer = 0;
  _resetState = true;
}

double flywheel_pid::getKp() { return _kP; }
double flywheel_pid::getKi() { return _kI; }
double flywheel_pid::getKd() { return _kD; }
double flywheel_pid::getKf() { return _kF; }