#include "AbstractLedStrip.h"

AbstractLedStrip::AbstractLedStrip(int s, int l, bool inv) {
  start = s;
  size = l;
  inverse = inv;
}

void AbstractLedStrip::setLedManager(LedManager * lm) {
  ledManager = lm;
}

void AbstractLedStrip::setLed(int led, int color) {
  if (inverse) {
    ledManager->setLed(start + size - led - 1, color);
  } else {
    ledManager->setLed(start + led, color);
  }
}

void AbstractLedStrip::doRainbow(int offset) {
  for (int i = 0; i < size; i++) {
    int color = (6 - (i % 6) + offset) % 6;
    setLed(i, color + 2);
  }
}

bool AbstractLedStrip::doExplosion(int offset) {
  for (int i = 0; i < size; i++) {
    if (i == offset || i == offset - 1) {
      setLed(i, 2);
    } else if (i == offset - 2 || i == offset - 3) {
      setLed(i, 3);
    } else if (i == offset - 4 || i == offset - 5) {
      setLed(i, 4);
    } else {
      setLed(i, 0);
    }
  }
  return (offset > size + 5);
}
