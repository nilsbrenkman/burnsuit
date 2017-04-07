#include "Sparkle.h"

Sparkle::Sparkle() {
  Serial.println("Sparkle started");
  state = 0; // waiting for next Sparkle
  mode = 0;
  nextEvent = 0;
}

void Sparkle::loop() {
  long now = millis();
  if (nextEvent < now) {
    switch (state) {
      case 0:
        state = 1;
        led = rand() % NUMBER_OF_LEDS;
        switch (mode) {
          case 0:
            ledManager->setLed(led, 1);
            break;
          case 1:
            int c = rand() % 6;
            ledManager->setLed(led, c + 2);
            break;
        }
        nextEvent = now + 100;
        break;
      case 1:
        state = 0;
        ledManager->setLed(led, 0);
        ledManager->show();
        nextEvent = now + (rand() % 500);
        break;
    }
  }
  if (state == 1) {
    int t = nextEvent - now;
    if (t < 50) {
      ledManager->setBrightness(255 * t / 100);
    } else {
      t = 100 - t;
      ledManager->setBrightness(255 * t / 100);
    }
    ledManager->show();
  }
}

void Sparkle::sleeve(int buttonid) {
  switch (buttonid) {
    case 3: mode = 0; break;
    case 4: mode = 1; break;
    default: break;
  }
}
