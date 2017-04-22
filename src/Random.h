#ifndef Random_H
#define Random_H

#include "AbstractProgram.h"

class Random : public AbstractProgram {
  public:
    Random();
    void loop();
    void mode(char letter);
  private:
    int strip;
    bool inverse;
    int hue;
};

#endif
