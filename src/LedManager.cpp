#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

LedManager::LedManager(RF24 * r, int i) {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(2)>(leds, NUMBER_OF_LEDS)
         .setCorrection(TypicalLEDStrip);
  radio = r;
  myId = i;
  brightness = 5;
  myOrange = blend(CRGB::Orange, CRGB::Red, 100);
}

void LedManager::setLedStrip(int i, AbstractLedStrip * ls) {
  ledStrip[i] = ls;
}

void LedManager::show() {
  FastLED.show();
}

void LedManager::setLed(int led, int color) {
  switch (color) {
    case 0: setLedWithColor(led, CRGB::Black);  break;
    case 1: setLedWithColor(led, CRGB::White);  break;
    case 2: setLedWithColor(led, CRGB::Red);    break;
    case 3: setLedWithColor(led, myOrange);     break;
    case 4: setLedWithColor(led, CRGB::Yellow); break;
    case 5: setLedWithColor(led, CRGB::Green);  break;
    case 6: setLedWithColor(led, CRGB::Blue);   break;
    case 7: setLedWithColor(led, CRGB::Purple); break;
    default: break;
  }
}

void LedManager::setLedWithColor(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::setBrightness(int b) {
  FastLED.setBrightness(b);
}

void LedManager::setBrightnessPersistent(int b, bool relative) {
  int newBrightness = b;
  if (relative) {
    newBrightness = brightness + b;
  }
  if (newBrightness < 1 || newBrightness > 5) {
    return;
  }
  brightness = newBrightness;
  Serial.print("brightness: ");
  Serial.println(brightness);
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  FastLED.show();
}

void LedManager::setAllLeds(int color) {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    setLed(i, color);
  }
}

void LedManager::clearAll() {
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  setAllLeds(0);
  FastLED.show();
}

bool LedManager::doProgramWithOffset(int program, int offset, bool andOr) {
  return doProgramWithColorAndOffset(program, 0, offset, andOr);
}

bool LedManager::doProgramWithColorAndOffset(int program, int color, int offset, bool andOr) {
  int const *colorScheme;
  switch (color) {
    case 0:  colorScheme = COLOR_SCHEME_RED;  break;
    case 1:  colorScheme = COLOR_SCHEME_BLUE; break;
    default: colorScheme = COLOR_SCHEME_BLUE; break;
  }
  bool done = andOr;
  for (int i = 0; i < NUMBER_OF_LEDSTRIPS; i++) {
    switch (program) {
      case 1: ledStrip[i]->doRainbow(offset); break;
      case 2: done &= ledStrip[i]->doExplosion(offset, colorScheme); break;
      case 3: done &= ledStrip[i]->doImplosion(offset, colorScheme); break;
      default: break;
    }
  }
  FastLED.show();
  return done;
}

int LedManager::getMyId() {
  return myId;
}

bool LedManager::sendToDevice(int deviceId, int data1, int data2, int data3) {
  radio->stopListening();
  radio->openWritingPipe(ADDRESSES[deviceId]);
  unsigned long data = combineDataFields(data1, data2, data3);
  bool result = radio->write(&data, sizeof(unsigned long));
  radio->startListening();
  return result;
}

unsigned long LedManager::combineDataFields(int data1, int data2, int data3) {
  unsigned long data = 0;
  data |= myId  << 24 & 0xff000000;
  data |= data1 << 16 & 0x00ff0000;
  data |= data2 <<  8 & 0x0000ff00;
  data |= data3       & 0x000000ff;
  return data;
}
