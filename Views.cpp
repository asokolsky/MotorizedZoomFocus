#include "MotorizedZoomFocus.h"

/**
 * Globals: views
 */
View *View::g_pActiveView = 0;


/**
 * Class View
 */

/**
 * Called once to set things up.
 */
void View::setup()
{
}

/** 
 * to be called from the main loop on the active view.  Do nothing by default. Return TRUE to update display
 */
boolean View::loop(unsigned long now)
{
  return false;
}


/** dummy defaults, children to overwrite */
bool View::onKeyDown(uint8_t vk) 
{
  return false;
}
bool View::onKeyAutoRepeat(uint8_t vk) 
{
  return false;
}
bool View::onLongKeyDown(uint8_t vk) 
{
  return false;
}
bool View::onKeyUp(uint8_t vk) 
{
  return false;
}
bool View::onKeyInactive()
{
  DEBUG_PRINTLN("View::onKeyInactive() => true");
  return true;
}


