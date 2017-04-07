#include "Slave.h"

Slave::Slave() {
  Serial.println("Going into slave mode");
}

void Slave::rf(unsigned long data) {
  int program = data / 100;
  switch (program) {
    case 1: doGroupRainbow(data % 100); break;
    default: break;
  }
}

void Slave::doGroupRainbow(int offset) {
  ledManager->setAllLeds(offset + 2);
  ledManager->show();
}
