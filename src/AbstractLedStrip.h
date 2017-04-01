#ifndef AbstractLedStrip_H
#define AbstractLedStrip_H

#include "LedManager.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class AbstractLedStrip {
  public:
    AbstractLedStrip(int start, int size, bool inverse);
    void init(LedManager * ledManager);
    void doRainbow(int offset);
  protected:
    int start;
    int size;
    int inverse;
    LedManager * ledManager;
    void setLed(int i, CRGB color);
};

#endif
