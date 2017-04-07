#include "ManualPulse.h"

ManualPulse::ManualPulse() {
  state = 0;
  nextEvent = 0;
}

void ManualPulse::loop() {
  if (state == 1) {
    long now = millis();
    if (nextEvent < now) {
      ledManager->setAllLeds(0);
      ledManager->show();
      state = 0;
    }
  }
}

void ManualPulse::sleeve(int buttonid) {
  if (state == 0) {
    ledManager->setAllLeds((buttonid + 5) % 8);
    ledManager->show();
    state = 1;
    nextEvent = millis() + 200;
  }
}

void ManualPulse::infrared(int value) {
  sleeve(value);
}
