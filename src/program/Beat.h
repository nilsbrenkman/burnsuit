#ifndef Beat_H
#define Beat_H

#include "AbstractProgram.h"
#include "application.h"
#include "MSGEQ7.h"

class Beat : public AbstractProgram {
  public:
    Beat(MSGEQ7 * s);
    void loop();
    void sleeve(int buttonid);
  private:
    MSGEQ7 * sound;
    int gain;
    int threshold;
};

#endif
