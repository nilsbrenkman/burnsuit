#include "Slave.h"

Slave::Slave() {
  Serial.println("Going into slave mode");
}

void Slave::rf(int senderId, int data1, int data2, int data3) {
  switch (data2) {
    case 1: doGroupRainbow(data3); break;
    default: break;
  }
}

void Slave::doGroupRainbow(int offset) {
  ledManager->setAllLeds(offset + 2);
  ledManager->show();
}
