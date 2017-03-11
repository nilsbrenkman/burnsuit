#include "ManualPulse.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

ManualPulse::ManualPulse() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}

void ManualPulse::loop() {
  // do nothing
}

void ManualPulse::clear() {
  // do nothing
}

void ManualPulse::sleeve(int buttonid) {
  for (int i = 0; i < NUM_LEDS; i++) {
    switch (buttonid) {
      case 5: leds[i] = CRGB::Red;    break;
      case 6: leds[i] = CRGB::Orange; break;
      case 7: leds[i] = CRGB::Yellow; break;
      case 0: leds[i] = CRGB::Green;  break;
      case 1: leds[i] = CRGB::Blue;   break;
      case 2: leds[i] = CRGB::Purple; break;
      default: break;
    }
  }
  FastLED.show();
  delay(200);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void ManualPulse::infrared(int value) {
  sleeve(value);
}
