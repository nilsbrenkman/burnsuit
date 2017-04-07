#include "Rainbow.h"

Rainbow::Rainbow() {
  speed = 2; // 0-4, 0 being fast
  brightness = 5;
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

void Rainbow::clear() {
  ledManager->clearAll();
}

void Rainbow::sleeve(int buttonid) {
  switch (buttonid) {
    case 0: speed = 0;                  break;
    case 1: if (speed > 0) { speed--; } break;
    case 2: if (speed < 4) { speed++; } break;
    case 5: setBrightness(5);           break;
    case 6: if (brightness < 5) { setBrightness(brightness+1); } break;
    case 7: if (brightness > 1) { setBrightness(brightness-1); } break;
    default: break;
  }
}

void Rainbow::setBrightness(int b) {
  brightness = b;
  Serial.print("brightness: ");
  Serial.println(brightness);
  ledManager->setBrightness( pow((b / 5.0), 2) * 255 );
}
