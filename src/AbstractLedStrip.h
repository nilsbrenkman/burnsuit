#ifndef AbstractLedStrip_H
#define AbstractLedStrip_H

#include <memory>
#include "LedManager.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class LedManager;

class AbstractLedStrip {
  public:
    AbstractLedStrip(int start, int size, bool inverse, bool left, int position);
    void setLedManager(LedManager * ledManager);
    void doRainbow(int offset);
    void doGradient(int offset);
    bool doExplosion(int offset, int const *colorScheme);
    bool doImplosion(int offset, int const *colorScheme);
    void doTrace(int offset, int const *colorScheme);
    void doRandom(int offset);
    bool doTraceWithTrail(int offset, int hue, bool programInverse);
  protected:
    void setLed(int led, int color);
    LedManager * ledManager;
    int start;
    int size;
    int inverse;
    bool left;
    int position;
    int ledStripOffset;
    bool ledStripInverse;
};

#endif
