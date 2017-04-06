#ifndef LedManager_H
#define LedManager_H

#include "Constants.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class LedManager {
  public:
    LedManager();
    void setLed(int i, CRGB color);
    void clearAll();
    void doProgramWithOffset(int program, int offset);
  private:
    CRGB leds[NUMBER_OF_LEDS];
};

#endif
