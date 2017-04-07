#include "AbstractLedStrip.h"

AbstractLedStrip::AbstractLedStrip(int s, int l, bool inv) {
  start = s;
  size = l;
  inverse = inv;
}

void AbstractLedStrip::setLedManager(LedManager * lm) {
  ledManager = lm;
}

void AbstractLedStrip::setLed(int i, CRGB color) {
  if (inverse) {
    ledManager->setLed(start + size - i - 1, color);
  } else {
    ledManager->setLed(start + i, color);
  }
}

void AbstractLedStrip::doRainbow(int offset) {
  for (int i = 0; i < size; i++) {
    int color = (i + offset) % 6;
    switch (color) {
      case 0: setLed(i, CRGB::Red);    break;
      case 1: setLed(i, CRGB::Orange); break;
      case 2: setLed(i, CRGB::Yellow); break;
      case 3: setLed(i, CRGB::Green);  break;
      case 4: setLed(i, CRGB::Blue);   break;
      case 5: setLed(i, CRGB::Purple); break;
    }
  }
}
