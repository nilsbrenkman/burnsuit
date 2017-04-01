#include "Rainbow.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

Rainbow::Rainbow(int s) {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  speed = s;
  brightness = 5;
  timeout = 0;
  offset = 0;
}

void Rainbow::loop() {
  if (timeout < millis()) {
    ledManager->doProgramWithOffset(offset);
    timeout = millis() + 1100 - (100 * speed);
    offset = (offset + 1) % 6;
  }
}

void Rainbow::clear() {
  ledManager->clearAll();
}

void Rainbow::sleeve(int buttonid) {
  switch (buttonid) {
    case 3: if (speed > 1)  { speed--; } break;
    case 4: if (speed < 10) { speed++; } break;
    case 5: setBrightness(5);            break;
    case 6: if (brightness < 5) { setBrightness(brightness+1); } break;
    case 7: if (brightness > 1) { setBrightness(brightness-1); } break;
    default: break;
  }
}

void Rainbow::setBrightness(int b) {
  brightness = b;
  Serial.print("brightness: ");
  Serial.println(brightness);
  FastLED.setBrightness( pow((b / 5.0), 2) * 255 );
  FastLED.show();
}
