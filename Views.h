#ifndef Views_h
#define Views_h

/**
 */
class View
{
protected:
  
public:  
  View() {}
  
  /** The Active View */
  static View *g_pActiveView;
  

  /** analog keyboard APIs where vk is one of VK_xxx */
  bool onKeyDown(uint8_t vk);
  bool onKeyAutoRepeat(uint8_t vk);
  bool onLongKeyDown(uint8_t vk);
  bool onKeyUp(uint8_t vk);
  bool onKeysInactive();

  
  /** to be called from the main loop on the active view.  Do nothing by default. return TRUE to update the display.  */
  bool loop(unsigned long now);

  /** might as well update GUI is its time*/
  void updateMaybe(unsigned long now);
  /** entire screen redraw */
  void update(unsigned long now);

#ifdef DEBUG
  void DUMP(const char *szText = 0) const;
#else
  void DUMP(const char *szText = 0) {}
#endif

  void activate() 
  {
    g_pActiveView = this;
  }
};

#endif

