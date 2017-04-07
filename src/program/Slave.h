#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"

class Slave : public AbstractProgram {
  public:
    Slave();
    void rf(unsigned long data);
  private:
    void doGroupRainbow(int offset);
};

#endif
