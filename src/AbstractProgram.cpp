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

void AbstractProgram::rf(unsigned long data) {
  // do nothing
}
