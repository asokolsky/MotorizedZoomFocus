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
 * Globals: display
 */
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_1_HW_I2C g_u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SH1106_128X64_NONAME_F_HW_I2C g_u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/**
 * Globals: reading battery voltage on A0 (through divider offcourse)
 */
BatteryMonitor g_batteryMonitor(pinBatteryMonitor);

Stepper g_stepperZoom(pinZoom1, pinZoom3, pinZoom2, pinZoom4);
Stepper g_stepperFocus(pinFocus1, pinFocus3, pinFocus2, pinFocus4);

class MyNavKeyPad: public /*AnalogNavigationKeypad*/ AnalogMicroNavigator
{
public:  
  /** this test if for a keyboard connected to A0 and A1 */
  MyNavKeyPad() : /* AnalogNavigationKeypad(A1, A2) */ AnalogMicroNavigator(pinKeyPad1, pinKeyPad2)
  {
    
  }
  bool onUserInActivity(unsigned long ulNow);
  bool onKeyAutoRepeat(uint8_t vks);
  bool onKeyDown(uint8_t vks);
  bool onLongKeyDown(uint8_t vks);
  bool onKeyUp(uint8_t vks);
};

bool MyNavKeyPad::onUserInActivity(unsigned long ulNow)
{
  DEBUG_PRINT("MyNavKeyPad::onUserInActivity ulNow="); DEBUG_PRINTDEC(ulNow); DEBUG_PRINTLN("");
  return false; 
}

bool MyNavKeyPad::onKeyAutoRepeat(uint8_t vks)
{
  DEBUG_PRINT("MyNavKeyPad::onKeyAutoRepeat vks="); DEBUG_PRNTLN(getKeyNames(vks));
  return false; 
}

bool MyNavKeyPad::onKeyDown(uint8_t vks)
{
  DEBUG_PRINT("MyNavKeyPad::onKeyDown vks="); DEBUG_PRNTLN(getKeyNames(vks));

  bool bRes = false;
  if(vks & (VK_RIGHT|VK_LEFT))
  {
    //DEBUG_PRINTLN("View::onKeyDown(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.startNow(uFocusMaxSpeed);
    g_stepperFocus.move((vks & VK_RIGHT) ? 4000 : -4000);
    bRes = true;
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  else if(vks & (VK_UP|VK_DOWN))
  {
    //DEBUG_PRINTLN("View::onKeyDown(VK_UP|VK_DOWN)");
    g_stepperFocus.startNow(uZoomMaxSpeed);
    g_stepperZoom.move((vks & VK_UP) ? 4000 : -4000);
    bRes = true;
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  else if(vks & VK_SEL)
  {
    //DEBUG_PRINTLN("View::onKeyDown(VK_SEL)");
    bRes = true;
  }
  return bRes;
}

bool MyNavKeyPad::onLongKeyDown(uint8_t vks)
{
  DEBUG_PRINT("MyNavKeyPad::onLongKeyDown vks="); DEBUG_PRNTLN(getKeyNames(vks));

  if(vks & (VK_RIGHT|VK_LEFT))
  {
    //DEBUG_PRINTLN("View::onLongKeyDown(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  else if(vks & (VK_UP|VK_DOWN))
  {
    //DEBUG_PRINTLN("View::onLongKeyDown(VK_UP|VK_DOWN)");
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  else if(vks & VK_SEL)
  {
    //DEBUG_PRINTLN("View::onLongKeyDown(VK_SEL)");
  }
  return false; 
}

bool MyNavKeyPad::onKeyUp(uint8_t vks)
{
  DEBUG_PRINT("MyNavKeyPad::onKeyUp vks="); DEBUG_PRNTLN(getKeyNames(vks));
  
  bool bRes = false;
  if(vks & (VK_RIGHT|VK_LEFT))
  {
    //DEBUG_PRINTLN("View::onKeyUp(VK_RIGHT|VK_LEFT)");
    g_stepperFocus.stopNow(); // this will also reset speed
    bRes = true;
    g_stepperFocus.DUMP("g_stepperFocus");
  }
  if(vks & (VK_UP|VK_DOWN))
  {
    //DEBUG_PRINTLN("View::onKeyUp(VK_UP|VK_DOWN)");
    g_stepperZoom.stopNow(); // this will also reset speed
    bRes = true;
    g_stepperZoom.DUMP("g_stepperZoom");
  }
  if(vks & VK_SEL)
  {
    //DEBUG_PRINTLN("View::onKeyUp(VK_SEL)");
    bRes = true;
  }
  return bRes;
}

MyNavKeyPad g_keyPad;


/** draw batttery gauge */
void drawBattery(u8g2_uint_t x, u8g2_uint_t y, uint8_t percentfull)
{
  u8g2_uint_t w = 14;
  u8g2_uint_t h = 8;
  g_u8g2.drawFrame(x, y, w, h);
  g_u8g2.drawVLine(x+w, y+3, h-6);
  x += 2;
  y += 2;
  h -= 4;
  w -= 4;
  if(percentfull > 10)
    g_u8g2.drawBox(x, y, (percentfull > 90) ? w : map(percentfull, 0, 100, 0, w), h);
}

/** draw title bar including batttery gauge */
void drawTitleBar()
{
  //g_u8g2.setFont(u8g2_font_profont10_mf);
  //char buf[40];
  //sprintf(buf, "%ims", iDisplayUpdate);
  //g_u8g2.drawStr(0, 8, buf);
  drawBattery(g_u8g2.getWidth() - 20, 0, g_batteryMonitor.getGauge());
}

void drawScreen()
{
  static const char szZoomIn[] = u8"\u2191";
  static const char szZoomOut[] = u8"\u2193";
  static const char szFocusIn[] = u8"\u2190";
  static const char szFocusOut[] = u8"\u2192";
  static const char szCenter[] = u8"\u25c7";

  static const char szZoomInPressed[] = u8"\u21d1";
  static const char szZoomOutPressed[] = u8"\u21d3";
  static const char szFocusInPressed[] = u8"\u21d0";
  static const char szFocusOutPressed[] = u8"\u21d2";
  static const char szCenterPressed[] = u8"\u25c8";

  //g_u8g2.setFont(u8g2_font_helvR14_tf);
  g_u8g2.setFont(u8g2_font_cu12_t_symbols);
  //g_u8g2.setFont(u8g2_font_unifont_t_symbols);
  //g_u8g2.setFontPosTop();  

  bool bPressed = g_keyPad.isKeyDown(VK_UP);
  u8g2_uint_t x = (g_u8g2.getWidth() /*- g_u8g2.getUTF8Width(szZoomIn)*/)/2; if(bPressed) x--;
  u8g2_uint_t y = 20;
  g_u8g2.drawUTF8(x, y, bPressed ? szZoomInPressed : szZoomIn);
  x = 0;
  y = 10 + g_u8g2.getHeight()/2;
  g_u8g2.drawUTF8(x,y, g_keyPad.isKeyDown(VK_LEFT) ? szFocusInPressed : szFocusIn);

  x = (g_u8g2.getWidth() /*- g_u8g2.getUTF8Width(szCenter)*/)/2 - 4;
  //y = g_u8g2.getHeight()/2;
  g_u8g2.drawUTF8(x,y, g_keyPad.isKeyDown(VK_SEL) ? szCenterPressed : szCenter);
  
  x = g_u8g2.getWidth() - g_u8g2.getStrWidth(szFocusOut);
  //y = g_u8g2.getHeight()/2;
  g_u8g2.drawUTF8(x, y, g_keyPad.isKeyDown(VK_RIGHT) ? szFocusOutPressed : szFocusOut);

  bPressed = g_keyPad.isKeyDown(VK_DOWN);
  x = (g_u8g2.getWidth() /*- g_u8g2.getUTF8Width(szZoomOut)*/)/2; if(bPressed) x--;
  y = g_u8g2.getHeight();
  g_u8g2.drawUTF8(x, y, bPressed ? szZoomOutPressed : szZoomOut);
}

void setup()
{  
  Serial.begin(115200);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("Zoom/Focus Rig!");

  g_batteryMonitor.update(millis());
  g_u8g2.begin();
  //g_u8g2.enableUTF8Print();
}

void loop()
{  
  unsigned long now = millis();

  bool bUpdateDisplay = false;
  {
    bool bRes1 = g_stepperZoom.run(); // runSpeed();
    bool bRes2 = g_stepperFocus.run(); // runSpeed();
    //DEBUG_PRINT("View::loop(), bRes1="); DEBUG_PRINTDEC(bRes1);
    //DEBUG_PRINT(" bRes2="); DEBUG_PRINTDEC(bRes2);
    //DEBUG_PRINTLN("");
    
    bUpdateDisplay = (bRes1 || bRes2);
  }

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

  // 
  // update the display
  //
  /*
  g_u8g2.clearBuffer();                 // clear the internal memory
  g_u8g2.sendBuffer();                  // transfer internal memory to the display
*/
  g_u8g2.firstPage();
  do {
    drawTitleBar();
    drawScreen();
  } while(g_u8g2.nextPage());

}


