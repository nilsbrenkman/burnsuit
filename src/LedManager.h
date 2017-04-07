#ifndef LedManager_H
#define LedManager_H

#include "Constants.h"
#include "AbstractLedStrip.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class AbstractLedStrip;

class LedManager {
  public:
    LedManager();
    void setLedStrip(int i, AbstractLedStrip * ledStrip);
    void show();
    void setLed(int led, int color);
    void setLedWithColor(int led, CRGB color);
    void setBrightness(int i);
    void setAllLeds(int color);
    void clearAll();
    void doProgramWithOffset(int program, int offset);
  private:
    CRGB leds[NUMBER_OF_LEDS];
    AbstractLedStrip * ledStrip[NUMBER_OF_LEDSTRIPS];
};

#endif
