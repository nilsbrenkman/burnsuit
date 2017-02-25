#include "Program1.h"

Program1::Program1(int t, int led) {
  T = t;
  LED = led;
}

void Program1::loop() {
  int t = millis() % T;
  if (t < T/2) {
    digitalWrite(LED, 1);
  } else {
    digitalWrite(LED, 0);
  }
}

void Program1::clear() {
  digitalWrite(LED, 0);
}

void Program1::sleeve(int buttonid) {
  // nothing to do
}
