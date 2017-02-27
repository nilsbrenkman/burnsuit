#ifndef Sparkle_H
#define Sparkle_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

enum State { on, off };
enum Mode { white, color };

class Sparkle : public AbstractProgram {
  public:
    Sparkle();
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    CRGB leds[4];
    int led;
    State state;
    Mode mode;
    long nextEvent;
};

#endif
