
#include "PCF8574.h"

class PCF8574_keypad : public PCF8574
{


  private:
  int time_last_press = 0;
  int time_last_release = 0;
  int interupt_pin;
  int press_cool_down;
  int release_cool_down;
  bool buttonflag = false;
  bool isattached = false;
  raw_interrupt_handler_t ISR_wrapper;
  int rowdata;
  int coldata;

  const int button_map[4][4] = {{1,2,3,12},{4,5,6,13},{7,8,9,14},{10,0,11,15}};

  public:
  PCF8574_keypad (int interupt_pin, int address, raw_interrupt_handler_t ISR_wrapper, int press_cool_down, int release_cool_down);
  int  getbutton();
  bool buttonpressed();
  void updateinterrupt();
  void ISR();

};
