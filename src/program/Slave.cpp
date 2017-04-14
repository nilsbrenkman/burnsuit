#include "Slave.h"

Slave::Slave() {
  Serial.println("Going into slave mode");
}

void Slave::loop() {
  switch (program) {
    case 2: doImplosionExplosion(); break;
    default: break;
  }
}

void Slave::rf(int senderId, int data1, int data2, int data3) {
  master = senderId;
  program = data1;
  switch (program) {
    case 1: doGroupRainbow(data3);  break;
    case 2: offset = 0; timeout = 0; state = 0; color = data3; break;
    default: break;
  }
}

void Slave::doGroupRainbow(int offset) {
  ledManager->setAllLeds(offset + 2);
  ledManager->show();
}

void Slave::doImplosionExplosion() {
  if (doEvent(50)) {
    if (state == 0 && ledManager->doProgramWithColorAndOffset(3, color, offset, true)) {
      state = 1;
      offset = 0;
      return;
    } else if (state == 1 && ledManager->doProgramWithColorAndOffset(2, color, offset, true)) {
      ledManager->sendToDevice(master, 0, 1, 0);  // send done to master
      program = 0;
      return;
    }
    offset++;
  }
}
