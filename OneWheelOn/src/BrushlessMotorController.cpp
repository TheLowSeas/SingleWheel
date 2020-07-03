
#include "BrushlessMotorController.h"
#include <clamp.h>

BrushlessMotorController::BrushlessMotorController(PinName motorPin,
                                                   int minRange, int maxRange,
                                                   int period,
                                                   bool canReverse) :
    _motorPin(motorPin)
{
    _minRange = minRange;
    _maxRange = maxRange;
    _period = period;
    _canReverse = canReverse;

    if (_canReverse)
        {
            _pulseWidth = (_maxRange + _minRange) / 2;
        }
    else
        {
            _pulseWidth = _minRange;
        }
}

BrushlessMotorController::BrushlessMotorController(PinName motorPin) :
    _motorPin(motorPin), _minRange(1000), _maxRange(2000)
{
    _canReverse = 1;
    _pulseWidth = (_maxRange + _minRange) / 2;
    setPeriod(20);
}

BrushlessMotorController::~BrushlessMotorController() {}

void BrushlessMotorController::update()
{
    _motorPin.pulsewidth_us(_pulseWidth);
}

void BrushlessMotorController::setPulsewidth(int width)
{
    int newWidth;
    newWidth = clampI(width, _minRange, _maxRange);
    _pulseWidth = newWidth;
}

void BrushlessMotorController::setPeriod(int period)
{
    _period = period;
    _motorPin.period_ms(_period);
}