#include "AbstractProgram.h"

void AbstractProgram::init(LedManager * lm) {
  ledManager = lm;
}

void AbstractProgram::loop() {
  // do nothing
}

void AbstractProgram::clear() {
  ledManager->clearAll();
}

void AbstractProgram::sleeve(int buttonid) {
  // do nothing
}

void AbstractProgram::infrared(int value) {
  // do nothing
}

void AbstractProgram::mode(char letter) {
  // do nothing
}

void AbstractProgram::rf(int senderId, int data1, int data2, int data3) {
  // do nothing
}

bool AbstractProgram::isMaster() {
  return false;
}

void AbstractProgram::selectMasterMode(int buttonid) {
  // do nothing
}

bool AbstractProgram::doEvent(int delay) {
  long now = millis();
  if (timeout < now) {
    timeout = millis() + delay;
    return true;
  }
  return false;
}
