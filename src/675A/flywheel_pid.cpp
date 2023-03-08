#include "main.h"
using namespace pros;

#define PID_SCALE 100

void flywheel_pid::init(flywheel_pid_settings pidSettings) {
  setKp(pidSettings.kP);
  setKi(pidSettings.kI);
  setKd(pidSettings.kD);
  setKff(pidSettings.kFF);
  _outLimits = pidSettings.outLimits;
  _dFilter = pidSettings.dFilter;
  _accLimit = pidSettings.accLimit * PID_SCALE;
  reset();
}

void flywheel_pid::init(float kP, float kI, float kD, float kFF,
                        float outLimits, float dFilter, float accLimit) {
  setKp(kP);
  setKi(kI);
  setKd(kD);
  setKff(kFF);
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
  pidSettings.kFF = getKff();
  pidSettings.outLimits = _outLimits;
  pidSettings.dFilter = _dFilter;
  pidSettings.accLimit = _accLimit;
  return pidSettings;
}

float flywheel_pid::spin(float input, float setpoint) {
  return spin(input, setpoint, 1);
}

float flywheel_pid::spin(float input, float setpoint, float attenuation) {

  float output = 0;
  float pControl = 0;
  float iControl = 0;
  float dControl = 0;
  float ffControl = 0;

  if (_enable) {

    if (_resetState) {
      _prevInput = input;
      _resetState = false;
    }

    float error = setpoint - input;

    // P
    pControl = error * _kP * attenuation;

    // I
    //  accumulator + accumulator limiting
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

    // D
    // low passing the velocity part
    if (_kD != 0) {

      _dBuffer =
          _dBuffer + (((input - _prevInput) - _dBuffer) / (_dFilter + 1));

      dControl = _dBuffer * _kD * attenuation;

    } else {
      _dBuffer = 0;
      dControl = 0;
    }

    // FF
    // feed forward control

    ffControl = setpoint * _kFF * attenuation;

    output = (pControl + iControl + dControl + ffControl) / PID_SCALE;

    _prevInput = input;

    // output limiting
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

void flywheel_pid::setKp(float kP) { _kP = kP; }
void flywheel_pid::setKi(float kI) { _kI = kI; }
void flywheel_pid::setKd(float kD) { _kD = kD; }
void flywheel_pid::setKff(float kFF) { _kFF = kFF; }

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

float flywheel_pid::getKp() { return _kP; }
float flywheel_pid::getKi() { return _kI; }
float flywheel_pid::getKd() { return _kD; }
float flywheel_pid::getKff() { return _kFF; }