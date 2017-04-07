#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"

class Slave : public AbstractProgram {
  public:
    Slave();
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    int brightness;
};

#endif
