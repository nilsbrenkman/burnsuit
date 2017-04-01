#ifndef LedManager_H
#define LedManager_H

#include "Constants.h"
#include "application.h"
#include "FastLED.h"
#include "AbstractLedStrip.h"
#include "MyFirstLedStrip.h"

FASTLED_USING_NAMESPACE;

class LedManager {
  public:
    LedManager();
    void setLed(int i, CRGB color);
    void clearAll();
  private:
    CRGB leds[NUMBER_OF_LEDS];
    AbstractLedStrip * ledStrips[1];
};

#endif
