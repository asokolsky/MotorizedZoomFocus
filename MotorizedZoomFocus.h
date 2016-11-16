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
//#include "Stepper.h"


