#ifndef PCF8574_H
#define PCF8574_H

#include "application.h"

class PCF8574
{
  protected:
    int address;

  public:
   PCF8574(int address) : address(address)
   {
     Wire.begin();
   }

   void write(int data)
   {
     Wire.beginTransmission(address);
     Wire.write(data);
     Wire.endTransmission();
   }

   int read()
   {
     Wire.requestFrom(address, 1);
     if(Wire.available())
     {
      return  Wire.read();
     }
     else
     {
       return -1;
     }
   }
};

#endif
