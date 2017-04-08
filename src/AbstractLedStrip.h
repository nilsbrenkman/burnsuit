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
    bool doExplosion(int offset, int const *colorScheme);
    bool doImplosion(int offset, int const *colorScheme);
  protected:
    LedManager * ledManager;
    int start;
    int size;
    int inverse;
    void setLed(int led, int color);
};

#endif
