#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUMBER_OF_LEDS);
}

void LedManager::setLed(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::clearAll() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

void LedManager::doProgramWithOffset(int program, int offset) {

}
