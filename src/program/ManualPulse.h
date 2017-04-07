#ifndef ManualPulse_H
#define ManualPulse_H

#include "AbstractProgram.h"
#include "application.h"

class ManualPulse : public AbstractProgram {
  public:
    ManualPulse();
    void loop();
    void sleeve(int buttonid);
    void infrared(int value);
  private:
    int state;
    long nextEvent;
    int offset;
};

#endif
