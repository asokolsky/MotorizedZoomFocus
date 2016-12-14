#ifndef STEPPER_H
#define STEPPER_H

#include <AccelStepper.h>

class Stepper : public AccelStepper
{  
public:
  Stepper(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);


#ifdef DEBUG
  void DUMP(const char *szText = 0) const;
#else
  void DUMP(const char *szText = 0) {}
#endif


  /** simple accessor */
  float getMaxSpeed() const {
    return _maxSpeed;
  }
  /** simple accessor */
  float getAcceleration() const {
    return _acceleration;
  }

private:
};


#endif

