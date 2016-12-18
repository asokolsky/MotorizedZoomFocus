#include "MotorizedZoomFocus.h"

/**
 * Globals: views
 */
View *View::g_pActiveView = 0;


/**
 * Class View
 */

/** 
 * to be called from the main loop on the active view.  Do nothing by default. Return TRUE to update display
 */
bool View::loop(unsigned long now)
{
  bool bRes1 = g_stepperZoom.run(); // runSpeed();
  bool bRes2 = g_stepperFocus.run(); // runSpeed();
  //DEBUG_PRINT("View::loop(), bRes1="); DEBUG_PRINTDEC(bRes1);
  //DEBUG_PRINT(" bRes2="); DEBUG_PRINTDEC(bRes2);
  //DEBUG_PRINTLN("");
  
  return (bRes1 || bRes2);
}


/** 
 *
 */
bool View::onKeyDown(uint8_t vk) 
{
  bool bRes = false;
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onKeyDown(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.startNow(uFocusMaxSpeed);
    g_stepperFocus.move((vk & VK_RIGHT) ? 4000 : -4000);
    bRes = true;
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  else if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onKeyDown(VK_UP|VK_DOWN)");
    g_stepperFocus.startNow(uZoomMaxSpeed);
    g_stepperZoom.move((vk & VK_UP) ? 4000 : -4000);
    bRes = true;
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  else if(vk & VK_SEL)
  {
    DEBUG_PRINTLN("View::onKeyDown(VK_SEL)");
    bRes = true;
  }
  return bRes;
}

bool View::onKeyAutoRepeat(uint8_t vk) 
{
  /*
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onKeyAutoRepeat(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  else if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onKeyAutoRepeat(VK_UP|VK_DOWN)");
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  else if(vk & VK_SEL)
  {
    DEBUG_PRINTLN("View::onKeyAutoRepeat(VK_SEL)");
  }
  */
  return false;
}

bool View::onLongKeyDown(uint8_t vk) 
{
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onLongKeyDown(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  else if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onLongKeyDown(VK_UP|VK_DOWN)");
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  else if(vk & VK_SEL)
  {
    DEBUG_PRINTLN("View::onLongKeyDown(VK_SEL)");
  }
  return false;
}

bool View::onKeyUp(uint8_t vk) 
{
  bool bRes = false;
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onKeyUp(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.stopNow(); // this will also reset speed
    bRes = true;
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onKeyUp(VK_UP|VK_DOWN)");
    g_stepperZoom.stopNow(); // this will also reset speed
    bRes = true;
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  if(vk & VK_SEL)
  {
    DEBUG_PRINTLN("View::onKeyUp(VK_SEL)");
    bRes = true;
  }
  return bRes;
}

bool View::onKeysInactive()
{
  /*DEBUG_PRINTLN("View::onKeysInactive() => true");
  g_stepperFocus.DUMP("g_stepperFocus");  
  g_stepperZoom.DUMP("g_stepperZoom");*/
  return true;
}


