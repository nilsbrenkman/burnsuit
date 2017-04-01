#include "Slave.h"

#define CHIPSET APA102
#define NUM_LEDS 4
#define DATA_PIN A1
#define CLOCK_PIN A0
#define COLOR_ORDER BGR

Slave::Slave(int l) {
  Serial.println("Going into slave mode");
  led = l;
}

void Slave::rf(unsigned long data) {
  int program = data / 10;
  switch (program) {
    case 1: blink(data % 10); break;
    default: break;
  }
}
void Slave::blink(int i) {
  Serial.println(i);
  if (i == 0) {
    digitalWrite(led, 0);
  } else if (i == 1) {
    digitalWrite(led, 1);
  }
}
