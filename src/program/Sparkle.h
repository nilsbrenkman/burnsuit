#ifndef Sparkle_H
#define Sparkle_H

#include "AbstractProgram.h"
#include "application.h"
#include "Constants.h"

class Sparkle : public AbstractProgram {
  public:
    Sparkle();
    void loop();
    void sleeve(int buttonid);
  private:
    int led;
    int mode;
};

#endif
