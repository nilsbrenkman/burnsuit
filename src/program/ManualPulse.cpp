#include "ManualPulse.h"

ManualPulse::ManualPulse() {
  Serial.println("Manual mode");
  state = 0;
  nextEvent = 0;
  offset = 0;
}

void ManualPulse::loop() {
  if (state == 1) {
    long now = millis();
    if (nextEvent < now) {
      ledManager->setAllLeds(0);
      ledManager->show();
      state = 0;
    }
  } else if (state == 2) {
    long now = millis();
    if (nextEvent < now) {
      offset++;
      Serial.println(offset);
      if (ledManager->doProgramWithOffset(2, offset, true)) {
        state = 0;
      } else {
        nextEvent = millis() + 50;
      }
    }
  }
}

void ManualPulse::sleeve(int buttonid) {
  if (state == 0) {
    switch (buttonid) {
      case 3:   // explosion
        Serial.println("Explosion");
        offset = 0;
        ledManager->doProgramWithOffset(2, offset, true);
        nextEvent = millis() + 50;
        state = 2;
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
