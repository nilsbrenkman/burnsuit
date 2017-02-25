#include "PCF8574_mombutt.h"

PCF8574_mombutt::PCF8574_mombutt(int interupt_pin, int address, raw_interrupt_handler_t ISR_wrapper, int press_cool_down, int release_cool_down) :
  PCF8574(address), press_cool_down(press_cool_down), release_cool_down (release_cool_down), interupt_pin (interupt_pin), ISR_wrapper (ISR_wrapper)
{
  pinMode(interupt_pin, INPUT_PULLUP);
  attachInterrupt(interupt_pin, ISR_wrapper, FALLING);
  write(0xFF);
}

int PCF8574_mombutt::getbutton()
{
  time_last_press = millis();
  for(int butt = 0; butt < 8; butt++)
   {
     if (button == buttonmap[butt]) return butt;
   }
  return -1;
}

bool PCF8574_mombutt::buttonpressed()
{
  if(!buttonflag)
  {
    return false;
  }
  else if(button == 0B11111110 ||
          button == 0B11111101 ||
          button == 0B11111011 ||
          button == 0B11110111 ||
          button == 0B11101111 ||
          button == 0B11011111 ||
          button == 0B10111111 ||
          button == 0B01111111 )
  {
    time_last_press = millis();
    buttonflag = false;
    return true;
  }
  else
  {
    buttonflag = false;
    time_last_release = millis();
    return false;
  }
}

void PCF8574_mombutt::updateinterrupt()
{
  if (!isattached &&
      millis() - press_cool_down > time_last_press &&
      millis() - release_cool_down > time_last_release)
  {
    write(0xFF);
    attachInterrupt(interupt_pin, ISR_wrapper, FALLING);
    isattached = true;
  }
}

void PCF8574_mombutt::ISR()
{
  detachInterrupt(interupt_pin);
  isattached = false;
  button = read();
  buttonflag = true;
}
