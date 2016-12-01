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
  bool bRes1 = g_stepperZoom.runSpeed();
  bool bRes2 = g_stepperFocus.runSpeed();
  return (bRes1 || bRes2);
}


/** dummy defaults, children to overwrite */
bool View::onKeyDown(uint8_t vk) 
{
  bool bRes = false;
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onKeyDown(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.setSpeed((vk & VK_RIGHT) ? iFocusSpeed : -iFocusSpeed);
    bRes = true;
  }
  else if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onKeyDown(VK_UP|VK_DOWN)");
    g_stepperZoom.setSpeed((vk & VK_UP) ? iZoomSpeed : -iZoomSpeed);
    bRes = true;
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
  DEBUG_PRINTLN("View::onKeyAutoRepeat()");
  return false;
}
bool View::onLongKeyDown(uint8_t vk) 
{
  DEBUG_PRINTLN("View::onLongKeyDown()");
  return false;
}
bool View::onKeyUp(uint8_t vk) 
{
  bool bRes = false;
  if(vk & (VK_RIGHT|VK_LEFT))
  {
    DEBUG_PRINTLN("View::onKeyUp(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.setSpeed(0);
    bRes = true;
  }
  if(vk & (VK_UP|VK_DOWN))
  {
    DEBUG_PRINTLN("View::onKeyUp(VK_UP|VK_DOWN)");
    g_stepperZoom.setSpeed(0);
    bRes = true;
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
  DEBUG_PRINTLN("View::onKeysInactive() => true");
  return true;
}


