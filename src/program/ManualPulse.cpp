#include "ManualPulse.h"

ManualPulse::ManualPulse() {
  Serial.println("Manual mode");
  state = 0;
  nextEvent = 0;
  offset = 0;
  color = 0;
}

void ManualPulse::loop() {
  if (state == 1) {
    long now = millis();
    if (nextEvent < now) {
      ledManager->setAllLeds(0);
      ledManager->show();
      state = 0;
    }
  } else if (state == 2 || state == 4) {
    long now = millis();
    if (nextEvent < now) {
      offset++;
      if (ledManager->doProgramWithOffset(state + color, offset, true)) {
        state = 0;
      } else {
        nextEvent = millis() + 400;
      }
    }
  }
}

void ManualPulse::sleeve(int buttonid) {
  if (state == 0) {
    switch (buttonid) {
      case 3:   // explosion
        offset = 0;
        color = (color + 1) % 2;
        ledManager->doProgramWithOffset(2 + color, offset, true);
        nextEvent = millis() + 400;
        state = 2;
        break;
      case 4:   // implosion
        offset = 0;
        color = (color + 1) % 2;
        ledManager->doProgramWithOffset(4 + color, offset, true);
        nextEvent = millis() + 400;
        state = 4;
        break;
      default:
        ledManager->setAllLeds((buttonid + 5) % 8);
        ledManager->show();
        nextEvent = millis() + 200;
        state = 1;
        break;
    }
  }
}

void ManualPulse::infrared(int value) {
  sleeve(value);
}
