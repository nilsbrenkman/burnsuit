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
    void clear();
    void sleeve(int buttonid);
    void mode(char letter);
  private:
    RF24 * radio;
    int myId;
    bool slavePresent[NUMBEROFDEVICES];
    int numberOfSlaves;
    void registerSlaves();
};

#endif
