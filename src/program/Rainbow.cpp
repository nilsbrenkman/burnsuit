#include "Rainbow.h"

Rainbow::Rainbow() {
  Serial.println("Rainbow started");
  speed = 2; // 0-4, 0 being fast
  timeout = 0;
  offset = 0;
}

void Rainbow::loop() {
  if (timeout < millis()) {
    ledManager->doProgramWithOffset(1, offset);
    timeout = millis() + (50 * pow(2, speed));
    offset = (offset + 1) % 6;
  }
}

void Rainbow::sleeve(int buttonid) {
  switch (buttonid) {
    case 0: speed = 0;                  break;
    case 1: if (speed > 0) { speed--; } break;
    case 2: if (speed < 4) { speed++; } break;
    default: break;
  }
}
