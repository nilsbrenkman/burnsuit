#ifndef LedManager_H
#define LedManager_H

#include <math.h>
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
    void setBrightness(int b);
    void setBrightnessPersistent(int b, bool relative);
    void setAllLeds(int color);
    void clearAll();
    bool doProgramWithOffset(int program, int offset, bool andOr);
  private:
    CRGB leds[NUMBER_OF_LEDS];
    CRGB myOrange;
    AbstractLedStrip * ledStrip[NUMBER_OF_LEDSTRIPS];
    int brightness;
};

#endif
