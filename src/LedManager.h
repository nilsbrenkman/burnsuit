#ifndef LedManager_H
#define LedManager_H

#include <math.h>
#include "particle-rf24.h"
#include "Constants.h"
#include "AbstractLedStrip.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class AbstractLedStrip;

class LedManager {
  public:
    LedManager(RF24 * radio, int myId);
    void setLedStrip(int i, AbstractLedStrip * ledStrip);
    void show();
    void setLed(int led, int color);
    void setLedWithColor(int led, CRGB color);
    void setBrightness(int b);
    void setBrightnessPersistent(int b, bool relative);
    void setAllLeds(int color);
    void clearAll();
    bool doProgramWithOffset(int program, int offset, bool andOr);
    bool doProgramWithColorAndOffset(int program, int color, int offset, bool andOr);
    int getMyId();
    bool sendToDevice(int deviceId, int data1, int data2, int data3);
  private:
    unsigned long combineDataFields(int data1, int data2, int data3);
    CRGB leds[NUMBER_OF_LEDS];
    CRGB myOrange;
    AbstractLedStrip * ledStrip[NUMBER_OF_LEDSTRIPS];
    RF24 * radio;
    int myId;
    int brightness;
};

#endif
