#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class Slave : public AbstractProgram {
  public:
    Slave();
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    CRGB leds[4];
    int brightness;
};

#endif
