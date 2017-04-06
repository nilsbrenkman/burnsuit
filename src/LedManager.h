#ifndef LedManager_H
#define LedManager_H

class LedManager {
  public:
    LedManager();
    void setLed(int i);
    void clearAll();
    void doProgramWithOffset(int program, int offset);
};

#endif
