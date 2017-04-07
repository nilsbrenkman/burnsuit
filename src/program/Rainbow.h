#ifndef Rainbow_H
#define Rainbow_H

#include <math.h>
#include "AbstractProgram.h"

class Rainbow : public AbstractProgram {
  public:
    Rainbow();
    void loop();
    void sleeve(int buttonid);
  private:
    void setBrightness(int b);
    int speed;
    int brightness;
    long timeout;
    int offset;
};

#endif
