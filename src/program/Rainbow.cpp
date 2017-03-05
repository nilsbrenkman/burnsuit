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
}

void Rainbow::loop() {
  int t = millis() / (speed * 50);
  for (int i = 0; i < NUM_LEDS; i++) {
    switch ((i + t) % 6) {
      case 0: leds[i] = CRGB::Red;    break;
      case 1: leds[i] = CRGB::Orange; break;
      case 2: leds[i] = CRGB::Yellow; break;
      case 3: leds[i] = CRGB::Green;  break;
      case 4: leds[i] = CRGB::Blue;   break;
      case 5: leds[i] = CRGB::Purple; break;
    }
  }
  FastLED.show();
}

void Rainbow::clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.setBrightness(255);
  FastLED.show();
}

void Rainbow::sleeve(int buttonid) {
  switch (buttonid) {
    case 3: if (speed > 1)  { speed--; } break;
    case 4: if (speed < 10) { speed++; } break;
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
  FastLED.setBrightness(255 * b / 5.0);
  FastLED.show();
}
