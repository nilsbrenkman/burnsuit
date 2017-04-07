#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUMBER_OF_LEDS);
}

void LedManager::setLedStrip(int i, AbstractLedStrip * ls) {
  ledStrip[i] = ls;
}

void LedManager::setLed(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::clearAll() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void LedManager::setBrightness(int i) {
  FastLED.setBrightness(i);
  FastLED.show();
}

void LedManager::doProgramWithOffset(int program, int offset) {
  for (int i = 0; i < NUMBER_OF_LEDSTRIPS; i++) {
    switch (program) {
      case 1: ledStrip[i]->doRainbow(offset); break;
      default: break;
    }
  }
  FastLED.show();
}
