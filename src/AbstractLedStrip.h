#ifndef AbstractLedStrip_H
#define AbstractLedStrip_H

#include "LedManager.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class AbstractLedStrip {
  public:
    AbstractLedStrip(int start, int size, bool inverse);
    void doRainbow(int offset);
  protected:
    void setLed(int i, CRGB color);
    int start;
    int size;
    int inverse;
};

#endif
