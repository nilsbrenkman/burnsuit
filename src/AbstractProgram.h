#ifndef AbstractProgram_H
#define AbstractProgram_H

class AbstractProgram {
  public:
     virtual void loop();
     virtual void clear();
     virtual void sleeve(int buttonid);
     virtual void infrared(int value);
};

#endif
