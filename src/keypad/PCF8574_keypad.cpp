

#include "PCF8574_keypad.h"

  PCF8574_keypad::PCF8574_keypad (int interupt_pin, int address, raw_interrupt_handler_t ISR_wrapper, int press_cool_down, int release_cool_down) :
    PCF8574(address), press_cool_down(press_cool_down), release_cool_down (release_cool_down), interupt_pin (interupt_pin), ISR_wrapper (ISR_wrapper)
  {
    write(0B00001111);
    pinMode(interupt_pin, INPUT_PULLUP);
    attachInterrupt(interupt_pin, ISR_wrapper, FALLING);
  }

  int  PCF8574_keypad::getbutton()
  {
    time_last_press = millis();
    int  row = 0;
    int  col = 0;
    for(int i = 0; i < 4; i++)
    {
      if(((rowdata >> i)     & 0B00000001) == 0)   row = i;
      if(((coldata >> i + 4) & 0B00000001) == 0)   col = i;
    }
    return button_map[row][col];
  }

  bool PCF8574_keypad::buttonpressed()
  {
    if(!buttonflag)
    {
      return false;
    }

    bool isvalidrow = (rowdata == 0B00001110) || (rowdata == 0B00001101) || (rowdata == 0B00001011)  || (rowdata == 0B00000111);
    bool isvalidcol = (coldata == 0B11100000) || (coldata == 0B11010000) || (coldata == 0B10110000)  || (coldata == 0B01110000);
    if(isvalidrow && isvalidcol)
    {
      time_last_press = millis();
      buttonflag = false;
      return true;
    }

    buttonflag = false;
    time_last_release = millis();
    return false;
  }

  void PCF8574_keypad::updateinterrupt()
  {
    if (!isattached &&
        millis() - press_cool_down > time_last_press &&
        millis() - release_cool_down > time_last_release)
    {
      attachInterrupt(interupt_pin, ISR_wrapper, FALLING);
      write(0B00001111);
      isattached = true;
    }
  }

  void PCF8574_keypad::ISR()
  {
    detachInterrupt(interupt_pin);
    rowdata = read();
    write(0B11110000);
    coldata = read();
    write(0B00001111);
    isattached = false;
    buttonflag = true;
  }
