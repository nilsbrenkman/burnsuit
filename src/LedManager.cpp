#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUMBER_OF_LEDS);
  ledStrips[0] = new MyFirstLedStrip(0, 4, false);
  for (int i = 0; i < sizeof(ledStrips); i++) {
    ledStrips[i]->init(this);
  }
}

void LedManager::setLed(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::clearAll() {
  for (int i = 0; i < sizeof(leds); i++) {
    leds[i] = CRGB::Black;
  }
}

void LedManager::doProgramWithOffset(int program, int offset) {
  for (int i = 0; i < sizeof(ledStrips); i++) {
    switch (program) {
      case 1: ledStrips[i]->doRainbow(offset); break;
      default: break;
    }
  }
  FastLED.show();
}
