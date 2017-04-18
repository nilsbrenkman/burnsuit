#include "AbstractLedStrip.h"

AbstractLedStrip::AbstractLedStrip(int st, int si, bool inv, bool lf, int pos) {
  start = st;
  size = si;
  inverse = inv;
  left = lf;
  position = pos;
  if (position == 0) {
    left ? ledStripOffset = 58 : ledStripOffset = 33;
    left ? ledStripInverse = true : ledStripInverse = false;
  } else if (position == 1) {
    left ? ledStripOffset = 62 : ledStripOffset = 30;
    left ? ledStripInverse = false : ledStripInverse = true;
  } else if (position == 2) {
    left ? ledStripOffset = 58 : ledStripOffset = 20;
    left ? ledStripInverse = false : ledStripInverse = true;
  } else if (position == 3 || position == 4) {
    left ? ledStripOffset = 96 : ledStripOffset = 0;
    left ? ledStripInverse = true : ledStripInverse = false;
  }
}

void AbstractLedStrip::setLedManager(LedManager * lm) {
  ledManager = lm;
}

void AbstractLedStrip::setLed(int led, int color) {
  if (led < 0 || led >= size) return; // Don't change another strip's leds
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

void AbstractLedStrip::doGradient(int offset) {
  int hue = offset;
  if (left) hue -= 5;
  for (int i = 0; i < size; i++) {
    if (inverse) {
      ledManager->setLedWithHue(start + size - i - 1, hue);
    } else {
      ledManager->setLedWithHue(start + i, hue);
    }
    left ? hue -= 5 : hue += 5;
  }
}

bool AbstractLedStrip::doExplosion(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if (offset == j + i) {
        setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) setLed(i, 0);
  }
  return (offset > size + colorSchemeSize);
}

bool AbstractLedStrip::doImplosion(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if (j == offset - MAX_LEDS_PER_LEDSTRIP + i + 1) {
        setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) setLed(i, 0);
  }
  return (offset > MAX_LEDS_PER_LEDSTRIP + colorSchemeSize - 2);
}

void AbstractLedStrip::doTrace(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if ((offset - ledStripOffset + 116) % 116 == i + j) {
        ledStripInverse ? setLed(size - i - 1, colorScheme[j+1]) : setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) ledStripInverse ? setLed(size - i - 1, 0) : setLed(i, 0);
  }
}

bool AbstractLedStrip::doTraceWithTrail(int offset, int hue, bool programInverse) {
  bool finalInverse = inverse ^ programInverse;
  if (finalInverse) {
    ledManager->setLedWithHue(start + size - offset - 1, hue);
  } else {
    ledManager->setLedWithHue(start + offset, hue);
  }
  return offset >= size - 1;
}

void AbstractLedStrip::doRandom(int offset) {
  int hue = (offset * 2 + (rand() % 10)) % 256;
  int led = rand() % size;
  ledManager->setLedWithHue(start + led, hue);
}
