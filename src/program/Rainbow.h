#ifndef Rainbow_H
#define Rainbow_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class Rainbow : public AbstractProgram {
  public:
    Rainbow(int speed);
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    void setBrightness(int b);
    CRGB leds[4];
    int speed;
    int brightness;
};

#endif
