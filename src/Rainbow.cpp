#include "Rainbow.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

Rainbow::Rainbow(int s) {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  speed = s;
}

void Rainbow::loop() {
  int t = millis() / (speed * 50);
  for (int i = 0; i < NUM_LEDS; i++) {
    if (((i + t) % 6) == 0) {
      leds[i] = CRGB::Red;
    } else if (((i + t) % 6) == 1) {
      leds[i] = CRGB::Orange;
    } else if (((i + t) % 6) == 2) {
      leds[i] = CRGB::Yellow;
    } else if (((i + t) % 6) == 3) {
      leds[i] = CRGB::Green;
    } else if (((i + t) % 6) == 4) {
      leds[i] = CRGB::Blue;
    } else if (((i + t) % 6) == 5) {
      leds[i] = CRGB::Purple;
    }
  }
  FastLED.show();
}

void Rainbow::clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void Rainbow::sleeve(int buttonid) {
  if (buttonid == 3) {
    if (speed > 1) {
      speed--;
    }
  } else if (buttonid == 4) {
    if (speed < 10) {
      speed++;
    }
  }
  Serial.print("speed: ");
  Serial.println(speed);
}
