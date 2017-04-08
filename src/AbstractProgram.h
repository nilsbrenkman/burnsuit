#ifndef AbstractProgram_H
#define AbstractProgram_H

#include "LedManager.h"

class AbstractProgram {
  public:
    void init(LedManager * ledManager);
    virtual void loop();
    virtual void clear();
    virtual void sleeve(int buttonid);
    virtual void infrared(int value);
    virtual void mode(char letter);
    virtual void rf(int senderId, int data1, int data2, int data3);
    virtual bool isMaster();
    virtual void selectMasterMode(int buttonid);
  protected:
    LedManager * ledManager;
};

#endif
