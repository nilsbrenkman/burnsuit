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
  } else if (state == 3 || state == 4) {
    if (doEvent(50)) {
      if (ledManager->doProgramWithColorAndOffset(state, color, offset, true)) {
        if (state == 4) {
          state = 3;
          offset = 0;
        } else {
          state = 0;
        }
      }
      offset++;
    }
  } else if (state == 5) {
    if (doEvent(50)) {
      ledManager->doProgramWithColorAndOffset(state, color, offset, false);
      offset = (offset + 1) % 116;
    }
  }
}

void ManualPulse::sleeve(int buttonid) {
  switch (buttonid) {
    case 0: color = 0; break;
    case 1: color = 1; break;
    case 2: color = 2; break;
    case 3:   // explosion
      state = 4;
      timeout = 0;
      offset = 0;
      break;
    case 4:
      state = 5;
      timeout = 0;
      offset = 0;
      break;
    default:
      ledManager->setAllLeds((buttonid + 5) % 8);
      ledManager->show();
      timeout = millis() + 200;
      state = 1;
      break;
  }
  ledManager->sendInfrared(buttonid);
}

void ManualPulse::infrared(int value) {
  sleeve(value);
}
