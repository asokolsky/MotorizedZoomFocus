/********************************************************\
 *                                                      *
 * Simple motorized Zoom/Focus Rig                      *
 *                                                      *
 * Alex Sokolsky                                        *
 *                                                      *
 *   v0.1  11/15/2016                                   *
 *                                                      *
\********************************************************/

//#include <vector>
//#include <string>
//#include <map>
//#include <climits>

//#include <ILI9341_t3.h>
//#include <Wire.h>
#include <AccelStepper.h>

/** CHAR is signed on AVR and unsigned on ARM!  WTF! */
typedef signed char schar_t;

//#define NODEBUG 1
#include "Trace.h"
//#include "ThumbStick.h"
#include "KeypadDuo.h"
#include "Views.h"
#include "Stepper.h"
#include "PCB.h"

/**
 * Steppers constants and globals
 */
const uint16_t uZoomSpeed = 200;
const uint16_t uZoomMaxSpeed = 1000;
const uint16_t uFocusSpeed = 200;
const uint16_t uFocusMaxSpeed = 1000;

extern Stepper g_stepperZoom;
extern Stepper g_stepperFocus;

