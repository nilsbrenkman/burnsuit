#ifndef LedStripL1_H
#define LedStripL1_H

#include "AbstractLedStrip.h"

class LedStripL1 : public AbstractLedStrip {
  public:
    LedStripL1(int start, int size, bool inverse, bool left, int position) : AbstractLedStrip(start, size, inverse, left, position) { }
};

#endif
