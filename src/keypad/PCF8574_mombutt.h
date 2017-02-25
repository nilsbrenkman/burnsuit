#include "PCF8574.h"

class PCF8574_mombutt : public PCF8574
{
  private:
  int time_last_press = 0;
  int time_last_release = 0;
  int interupt_pin;
  int press_cool_down;
  int release_cool_down;
  int button = -1;
  bool buttonflag = false;
  bool isattached = false;
  raw_interrupt_handler_t ISR_wrapper;
  int buttonmap[8] = {255-1, 255-2, 255-4, 255-8, 255-16, 255-32, 255-64, 255-128};

  public:
  PCF8574_mombutt(int interupt_pin, int address, raw_interrupt_handler_t ISR_wrapper, int press_cool_down, int release_cool_down);
  int  getbutton();
  bool buttonpressed();
  void updateinterrupt();
  void ISR();
};
