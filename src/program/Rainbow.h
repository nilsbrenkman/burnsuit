#ifndef Rainbow_H
#define Rainbow_H

#include "AbstractProgram.h"
#include "application.h"
#include "FastLED.h"
#include <math.h>

class Rainbow : public AbstractProgram {
  public:
    Rainbow(int speed);
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    void setBrightness(int b);
    int speed;
    int brightness;
    long timeout;
    int offset;
};

#endif
