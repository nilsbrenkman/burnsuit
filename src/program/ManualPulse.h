#ifndef ManualPulse_H
#define ManualPulse_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class ManualPulse : public AbstractProgram {
  public:
    ManualPulse();
    void loop();
    void clear();
    void sleeve(int buttonid);
    void infrared(int value);
  private:
    CRGB leds[4];
    int speed;
};

#endif
