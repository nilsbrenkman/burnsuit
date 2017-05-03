#include "Slave.h"

Slave::Slave() {
  Serial.println("Going into slave mode");
}

void Slave::loop() {
  switch (program) {
    case 2: doImplosionExplosion(); break;
    case 4: doManual();             break;
    default: break;
  }
}

void Slave::rf(int senderId, int data1, int data2, int data3) {
  master = senderId;
  program = data1;
  switch (program) {
    case 2: offset = 0; timeout = 0; state = 0; color = data3; break;
    case 3: doGroupRainbow(data3);  break;
    case 4: offset = 0; timeout = 0; state = data2; color = data3; doManual(); break;
    default: break;
  }
}

void Slave::doGroupRainbow(int offset) {
  ledManager->setAllLeds(offset + 2);
  ledManager->show();
}

void Slave::doImplosionExplosion() {
  if (doEvent(50)) {
    if (state == 0 && ledManager->doProgramWithColorAndOffset(4, color, offset, true)) {
      state = 1;
      offset = 0;
      return;
    } else if (state == 1 && ledManager->doProgramWithColorAndOffset(3, color, offset, true)) {
      ledManager->sendToDevice(master, 0, 1, 0);  // send done to master
      program = 0;
      return;
    }
    offset++;
  }
}

void Slave::doManual() {
  if (doEvent(50)) {
    switch (state) {
      case 2:
        if (ledManager->doProgramWithColorAndOffset(3, color, offset, true)) {
          state = 0;
          return;
        }
        offset++;
        break;
      case 3:
        if (ledManager->doProgramWithColorAndOffset(4, color, offset, true)) {
          state = 2;
          offset = 0;
          return;
        }
        offset++;
        break;
      case 4:
        int const *colorScheme;
        switch (color) {
          case 0:  colorScheme = COLOR_SCHEME_RED;     break;
          case 1:  colorScheme = COLOR_SCHEME_BLUE;    break;
          case 2:  colorScheme = COLOR_SCHEME_RAINBOW; break;
          default: colorScheme = COLOR_SCHEME_BLUE;    break;
        }
        if (offset < colorScheme[0]) {
          offset++;
          ledManager->setAllLeds(colorScheme[offset]);
        } else {
          ledManager->setAllLeds(0);
          state = 0;
        }
        ledManager->show();
        break;
      default: break;
    }
  }
}
