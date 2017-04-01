#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class Slave : public AbstractProgram {
  public:
    Slave(int led);
    void rf(unsigned long data);
  private:
    void blink(int i);
    int led;
};

#endif
