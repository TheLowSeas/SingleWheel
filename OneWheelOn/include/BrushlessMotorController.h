#pragma once
#include "mbed.h"

class BrushlessMotorController
{
  private:
    PwmOut _motorPin;
    int _minRange;
    int _maxRange;
    int _pulseWidth;
    int _period;
    bool _canReverse;

  public:
    /*used to contruct with full custom setting
  Range is the pulseWidth range in microseconds
  Period is in miliseconds
  canReverse is a bool to determine if the motor is set up to be 3D */
    BrushlessMotorController(PinName MotorPin, int minRange, int MaxRange,
                             int period, bool canReverse);

    /*used to contruct with most common input for a brushless Motor
  range is 1000 microseonds to 2000 microseconds
  period is 20 miliseconds or 50hz
  can reverse is true
  */
    BrushlessMotorController(PinName MotorPin);

    ~BrushlessMotorController();

    /*updates the newest values for pulsewidth*/
    void update();

    /*sets the local value for Pulsewidth to be used with next update() call
  inputed value will be assumed to be microseconds
  inputed value will be clamped within the constructed range*/
    void setPulsewidth(int width);

    /*sets the local value for period and sets the value of the period of the
  motor period will be assumed to be in miliseconds*/
    void setPeriod(int period);
};
