#ifndef Constants_H
#define Constants_H

#include "application.h"

const String DEVICEIDS[4]= {"2d0055000851353531343431",  // mufasa
                            "410033000347353138383138",  // linquenda
                            "2a004e001551353531343431",  // simba
                            "300023000851353531343431"}; // jorien
const byte ADDRESSES[4][6] = {"mufas", "linqu", "simba", "jorie"};
const int NUMBER_OF_DEVICES = 4;
const int NUMBER_OF_LEDS = 4;
const int NUMBER_OF_LEDSTRIPS = 2;

#endif
