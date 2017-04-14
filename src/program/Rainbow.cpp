#include "Rainbow.h"

Rainbow::Rainbow() {
  Serial.println("Rainbow started");
  speed = 2; // 0-4, 0 being fast
  timeout = 0;
  offset = 0;
  state = 0;
}

void Rainbow::loop() {
  if (state == 0 && doEvent(50 * pow(2, speed))) {
    ledManager->doProgramWithOffset(1, offset, false);
    offset = (offset + 1) % 6;
  } else if (state == 1 && doEvent(5 * pow(2, speed))) {
    ledManager->doProgramWithOffset(2, offset, false);
    offset++;
  }
}

void Rainbow::sleeve(int buttonid) {
  switch (buttonid) {
    case 0: speed = 0;                                 break;
    case 1: if (speed > 0)  { speed--; }               break;
    case 2: if (speed < 4)  { speed++; }               break;
    case 3: if (state == 1) { state = 0; offset = 0; } break;
    case 4: if (state == 0) { state = 1; offset = 0; } break;
    default: break;
  }
}
