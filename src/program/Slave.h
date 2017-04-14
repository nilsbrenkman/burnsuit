#ifndef Slave_H
#define Slave_H

#include "AbstractProgram.h"
#include "application.h"

class Slave : public AbstractProgram {
  public:
    Slave();
    void loop();
    void rf(int senderId, int data1, int data2, int data3);
  private:
    void doGroupRainbow(int offset);
    void doImplosionExplosion();
    bool doEvent(int delay);
    int master;
    int program;
    int offset;
    long nextEvent;
    int state;
    int color;
};

#endif
