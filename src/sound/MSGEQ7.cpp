#include "MSGEQ7.h"

MSGEQ7::MSGEQ7(const int pin_reset, const int pin_strobe, const int pin_data):
               pin_reset(pin_reset), pin_strobe(pin_strobe), pin_data(pin_data)
{
  pinMode(pin_strobe, OUTPUT);
  pinMode(pin_reset,  OUTPUT);
}

void MSGEQ7::process(const int gain, const int threshold)
{
  for (int i = 0; i < 7; i++)
  {
    freqVolume[i] = gain*freqVolume[i];
    freqVolume[i] = constrain(freqVolume[i], threshold, 4096);
    freqVolume[i] = map(freqVolume[i], threshold, 4096, 0, 255);
   }
}

void MSGEQ7::read_robust()
{
  const int num_samples = 5;
  int min[7] = {4096, 4096, 4096, 4096, 4096, 4096, 4096};
  int max[7] = {0, 0, 0, 0, 0, 0 ,0 };
  int data;
  int smart_mean[7] = {0,0,0,0,0,0,0};

  for (int i = 0; i < num_samples; i++)
  {
    read();
    for (int j = 0; j < 7; j++)
    {
       data = freqVolume[j];
       if (data > max[j]) max[j] = data;
       if (data < min[j]) min[j] = data;
       smart_mean[j] += data;
    }
  }

  for (int j = 0; j < 7; j++)
  {
    freqVolume[j] = (smart_mean[j] - min[j] - max[j])/(num_samples - 2);
  }
}

void MSGEQ7::read()
{
  digitalWrite(pin_reset, HIGH);
  digitalWrite(pin_strobe, HIGH);
  delayMicroseconds(50);
  digitalWrite(pin_strobe, LOW);
  delayMicroseconds(50);
  digitalWrite(pin_reset, LOW);
  digitalWrite(pin_strobe, HIGH);
  delayMicroseconds(80);

  for (int i = 0; i < 7; i++)
  {
    digitalWrite(pin_strobe, LOW);
    delayMicroseconds(30);
    freqVolume[i] = analogRead(pin_data);
    delayMicroseconds(50);
    digitalWrite(pin_strobe, HIGH);
   }
}
