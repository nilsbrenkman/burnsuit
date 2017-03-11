#include "Sparkle.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

Sparkle::Sparkle() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  State state = off; // waiting for next Sparkle
  Mode mode = white;
  nextEvent = millis() + (rand() % 500);
}

void Sparkle::loop() {
  long now = millis();
  if (nextEvent < now) {
    switch (state) {
      case off:
        state = on;
        led = rand() % NUM_LEDS;
        switch (mode) {
          case white:
            leds[led] = CRGB::White;
            break;
          case color:
            int c = rand() % 6;
            switch (c) {
              case 0: leds[led] = CRGB::Red;    break;
              case 1: leds[led] = CRGB::Orange; break;
              case 2: leds[led] = CRGB::Yellow; break;
              case 3: leds[led] = CRGB::Green;  break;
              case 4: leds[led] = CRGB::Blue;   break;
              case 5: leds[led] = CRGB::Purple; break;
            }
            break;
        }
        nextEvent = now + 100;
        FastLED.show();
        break;
      case on:
        state = off;
        leds[led] = CRGB::Black;
        nextEvent = now + (rand() % 500);
        FastLED.show();
        break;
    }
  }
  if (state == on) {
    int t = nextEvent - now;
    if (t < 50) {
      FastLED.setBrightness(255 * t / 100);
    } else {
      t = 100 - t;
      FastLED.setBrightness(255 * t / 100);
    }
    FastLED.show();
  }
}

void Sparkle::clear() {
  FastLED.setBrightness(255);
  if (state == on) {
    leds[led] = CRGB::Black;
    FastLED.show();
  }
}

void Sparkle::sleeve(int buttonid) {
  switch (buttonid) {
    case 3: mode = white; break;
    case 4: mode = color; break;
    default: break;
  }
}
