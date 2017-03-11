#include "Slave.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

Slave::Slave() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  brightness = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void Slave::loop() {
  int t = (millis() / 200) % 255;
  if (t != brightness) {
    brightness = t;
    FastLED.setBrightness(255);
    FastLED.show();
    Serial.print("brightness: ");
    Serial.println(brightness);
  }
}

void Slave::clear() {
  // do nothing
}

void Slave::sleeve(int buttonid) {
  // do nothing
}
