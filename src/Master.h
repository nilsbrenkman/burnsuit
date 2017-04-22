#ifndef Master_H
#define Master_H

#include <math.h>
#include "Constants.h"
#include "AbstractProgram.h"
#include "application.h"

class Master : public AbstractProgram {
  public:
    Master();
    void loop();
    void sleeve(int buttonid);
    void mode(char letter);
    void rf(int senderId, int data1, int data2, int data3);
    bool isMaster();
    void selectMasterMode(int buttonid);
  private:
    void registerSlaves();
    bool sendToDevice(int id, unsigned long data);
    void doGroupRainbow();
    void doImplosionExplosion();
    void doManual(int buttonid);
    bool slavePresent[NUMBER_OF_DEVICES];
    int numberOfSlaves;
};

#endif
