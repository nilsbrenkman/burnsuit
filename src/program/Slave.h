#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"

class Slave : public AbstractProgram {
  public:
    Slave();
    void rf(int senderId, int data1, int data2, int data3);
  private:
    void doGroupRainbow(int offset);
};

#endif
