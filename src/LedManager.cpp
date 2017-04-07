#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUMBER_OF_LEDS);
  brightness = 5;
}

void LedManager::setLedStrip(int i, AbstractLedStrip * ls) {
  ledStrip[i] = ls;
}

void LedManager::show() {
  FastLED.show();
}

void LedManager::setLed(int led, int color) {
  switch (color) {
    case 0: setLedWithColor(led, CRGB::Black);  break;
    case 1: setLedWithColor(led, CRGB::White);  break;
    case 2: setLedWithColor(led, CRGB::Red);    break;
    case 3: setLedWithColor(led, CRGB::Orange); break;
    case 4: setLedWithColor(led, CRGB::Yellow); break;
    case 5: setLedWithColor(led, CRGB::Green);  break;
    case 6: setLedWithColor(led, CRGB::Blue);   break;
    case 7: setLedWithColor(led, CRGB::Purple); break;
    default: break;
  }
}

void LedManager::setLedWithColor(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::setBrightness(int b) {
  FastLED.setBrightness(b);
}

void LedManager::setBrightnessPersistent(int b, bool relative) {
  int newBrightness = b;
  if (relative) {
    newBrightness = brightness + b;
  }
  if (newBrightness < 1 || newBrightness > 5) {
    return;
  }
  brightness = newBrightness;
  Serial.print("brightness: ");
  Serial.println(brightness);
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  FastLED.show();
}

void LedManager::setAllLeds(int color) {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    setLed(i, color);
  }
}

void LedManager::clearAll() {
  setBrightnessPersistent(0, true);
  setAllLeds(0);
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
