#include "Sparkle.h"

Sparkle::Sparkle() {
  Serial.println("Sparkle started");
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
        led = rand() % NUMBER_OF_LEDS;
        switch (mode) {
          case white:
            ledManager->setLed(led, CRGB::White);
            break;
          case color:
            int c = rand() % 6;
            switch (c) {
              case 0: ledManager->setLed(led, CRGB::Red);    break;
              case 1: ledManager->setLed(led, CRGB::Orange); break;
              case 2: ledManager->setLed(led, CRGB::Yellow); break;
              case 3: ledManager->setLed(led, CRGB::Green);  break;
              case 4: ledManager->setLed(led, CRGB::Blue);   break;
              case 5: ledManager->setLed(led, CRGB::Purple); break;
            }
            break;
        }
        nextEvent = now + 100;
        break;
      case on:
        state = off;
        ledManager->setLed(led, CRGB::Black);
        nextEvent = now + (rand() % 500);
        break;
    }
  }
  if (state == on) {
    int t = nextEvent - now;
    if (t < 50) {
      ledManager->setBrightness(255 * t / 100);
    } else {
      t = 100 - t;
      ledManager->setBrightness(255 * t / 100);
    }
  }
}

void Sparkle::clear() {
  ledManager->clearAll();
}

void Sparkle::sleeve(int buttonid) {
  switch (buttonid) {
    case 3: mode = white; break;
    case 4: mode = color; break;
    default: break;
  }
}
