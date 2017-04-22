#ifndef MSGEQ7_H
#define MSGEQ7_H

#include "application.h"

class MSGEQ7
{
    private:
    int pin_reset;
    int pin_strobe;
    int pin_data;

    public:
    MSGEQ7(const int pin_reset, const int pin_strobe, const int pin_data);
    void read();
    void read_robust();
    void process(const int gain, const int threshold);
    int freqVolume[7];
};

#endif
