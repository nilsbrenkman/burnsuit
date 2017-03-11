#ifndef Program1_H
#define Program1_H

#include "AbstractProgram.h"
#include "application.h"

class Program1 : public AbstractProgram {
  public:
    Program1(int t, int led);
    void loop();
    void clear();
    void sleeve(int buttonid);
  private:
    int LED;
    int T;
};

#endif
