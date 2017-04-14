#ifndef Constants_H
#define Constants_H

#include "application.h"

const String DEVICEIDS[8]= {"290057001551353531343431",   // rafiki:
              							"300023000851353531343431",   // jorien:
              							"2d0055000851353531343431",   // mufasa:
              							"390054000851353531343431",   // nala:
              							"260024001551353531343431",   // pumba:
              							"2a004e001551353531343431",   // simba:
              							"210048000851353531343431",   // timon:
              							"410033000347353138383138"};  // zazu:
const byte ADDRESSES[8][6] = {"rafik", "jorie", "mufas", "nalax",
                              "pumba", "simba", "timon", "zazux"};
const int NUMBER_OF_DEVICES = 8;

const int NUMBER_OF_LEDS        = 4;
const int NUMBER_OF_LEDSTRIPS   = 2;
const int MIN_LEDS_PER_LEDSTRIP = 2;
const int MAX_LEDS_PER_LEDSTRIP = 2;
// const int NUMBER_OF_LEDS        = 254;
// const int NUMBER_OF_LEDSTRIPS   = 10;
// const int MIN_LEDS_PER_LEDSTRIP = 20;
// const int MAX_LEDS_PER_LEDSTRIP = 38;

const int COLOR_SCHEME_RED[7] =  {6, 2, 2, 3, 3, 4, 4}; // first integer is size
const int COLOR_SCHEME_BLUE[3] = {2, 6, 7};

#endif
