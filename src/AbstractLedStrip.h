#ifndef AbstractLedStrip_H
#define AbstractLedStrip_H

#include <memory>
#include "LedManager.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class LedManager;

class AbstractLedStrip {
  public:
    AbstractLedStrip(int start, int size, bool inverse);
    void setLedManager(LedManager * ledManager);
    void doRainbow(int offset);
  protected:
    LedManager * ledManager;
    int start;
    int size;
    int inverse;
    void setLed(int i, CRGB color);
};

#endif
