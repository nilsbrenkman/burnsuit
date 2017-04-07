#ifndef Master_H
#define Master_H

#include "Constants.h"
#include "AbstractProgram.h"
#include "application.h"
#include "particle-rf24.h"

class Master : public AbstractProgram {
  public:
    Master(RF24 * radio, int myId);
    void loop();
    void sleeve(int buttonid);
    void mode(char letter);
    bool isMaster();
    void selectMasterMode(int buttonid);
  private:
    void registerSlaves();
    bool sendToDevice(int id, unsigned long data);
    void doGroupRainbow();
    RF24 * radio;
    int myId;
    bool slavePresent[NUMBER_OF_DEVICES];
    int numberOfSlaves;
    int program;
    int offset;
    long timeout;
};

#endif
