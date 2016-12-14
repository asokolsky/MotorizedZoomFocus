/********************************************************\
 *                                                      *
 * Simple motorized zoom/focus rig                      *
 *                                                      *
 * Alex Sokolsky                                        *
 *                                                      *
 *   v0.1  11/15/2016                                   *
 *                                                      *
\********************************************************/

#include "MotorizedZoomFocus.h"
#include "BatteryMonitor.h"


//#define NODEBUG 1

/** 
 *  Necessary for STL to link
 */
/*extern "C"{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
}*/


/**
 * Globals: reading battery voltage on A0 (through divider offcourse)
 */
BatteryMonitor g_batteryMonitor(A0);

const uint8_t pinZoom1 = 2;
const uint8_t pinZoom2 = 3;
const uint8_t pinZoom3 = 4;
const uint8_t pinZoom4 = 5;
Stepper g_stepperZoom(pinZoom1, pinZoom2, pinZoom3, pinZoom4);

const uint8_t pinFocus1 = 6;
const uint8_t pinFocus2 = 7;
const uint8_t pinFocus3 = 8;
const uint8_t pinFocus4 = 9;
Stepper g_stepperFocus(pinFocus1, pinFocus2, pinFocus3, pinFocus4);

static View g_view;

void setup()
{  
  Serial.begin(9600);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("Zoom/Focus Rig!");

  g_batteryMonitor.update(millis());

  g_view.activate();
}

void loop()
{  
  unsigned long now = millis();

  bool bUpdateDisplay = false;
  if(View::g_pActiveView != 0)
    bUpdateDisplay = View::g_pActiveView->loop(now);

  if(g_keyPad.getAndDispatchKey(now))
  {
    bUpdateDisplay = true;
  } 
  /*else if(g_serialCommandInterpreter.available()) 
  {
    DEBUG_PRINTLN("Read a command from serial line!");
    g_serialCommandInterpreter.readAndDispatch();
    bUpdateDisplay = true;
  } */
  else if(g_batteryMonitor.updateMaybe(now))
  {    
    bUpdateDisplay = true;
  }
  //if(bUpdateDisplay) g_ci.updateDisplay(now);
  //if(bUpdateDisplay && View::g_pActiveView != 0) View::g_pActiveView->update(now);
}


