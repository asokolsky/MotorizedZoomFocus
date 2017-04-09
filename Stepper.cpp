#include "MotorizedZoomFocus.h"
//#include "Stepper.h"

Stepper::Stepper(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) :
  AccelStepper(AccelStepper::HALF4WIRE, pin1, pin2, pin3, pin4)
{
  setMaxSpeed(1000);
  setAcceleration(50);
}

#ifdef DEBUG
void Stepper::DUMP(const char *szText /*= 0*/) const
{
  if(szText != 0) {
    DEBUG_PRNT(szText);
  }
  DEBUG_PRINT(" Stepper@"); DEBUG_PRINTDEC((int)this); 
  
  DEBUG_PRINT(" _currentPos="); DEBUG_PRINTDEC((int)_currentPos);   
  DEBUG_PRINT(" _targetPos="); DEBUG_PRINTDEC((int)_targetPos);   
  DEBUG_PRINT(" _speed="); DEBUG_PRINTDEC((int)_speed);
  DEBUG_PRINT(" _maxSpeed="); DEBUG_PRINTDEC((int)_maxSpeed);
  DEBUG_PRINT(" _acceleration="); DEBUG_PRINTDEC((int)_acceleration);
  
  DEBUG_PRINTLN("");
}
#endif


