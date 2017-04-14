#include "ManualPulse.h"

ManualPulse::ManualPulse() {
  Serial.println("Manual mode");
  state = 0;
  timeout = 0;
  offset = 0;
  color = 0;
}

void ManualPulse::loop() {
  if (state == 1) {
    if (doEvent(0)) {
      ledManager->setAllLeds(0);
      ledManager->show();
      state = 0;
    }
  } else if (state == 2 || state == 3) {
    if (doEvent(0)) {
      offset++;
      if (ledManager->doProgramWithColorAndOffset(state, color, offset, true)) {
        state = 0;
      } else {
        timeout = millis() + 50;
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
        ledManager->doProgramWithColorAndOffset(2, color, offset, true);
        timeout = millis() + 50;
        state = 2;
        break;
      case 4:   // implosion
        offset = 0;
        color = (color + 1) % 2;
        ledManager->doProgramWithColorAndOffset(3, color, offset, true);
        timeout = millis() + 50;
        state = 3;
        break;
      default:
        ledManager->setAllLeds((buttonid + 5) % 8);
        ledManager->show();
        timeout = millis() + 200;
        state = 1;
        break;
    }
  }
}

void ManualPulse::infrared(int value) {
  sleeve(value);
}
