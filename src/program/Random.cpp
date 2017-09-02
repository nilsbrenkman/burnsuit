#include "Random.h"

Random::Random() {
  timeout = 0;
  offset = 0;
  state = 0;
}

void Random::loop() {
  switch (state) {
    case 0:
      if (doEvent(50)) {
        ledManager->doProgramWithOffset(6, offset, false);
        offset++;
      }
      ledManager->fadeToBlack();
      break;
    case 1:
      if (doEvent(50)) {
        if (ledManager->doTraceWithTrail(strip, offset, hue, inverse)) {
          offset = 0;
          int random = rand() % (NUMBER_OF_LEDSTRIPS - 1);
          strip = (strip + random + 1) % NUMBER_OF_LEDSTRIPS;
          inverse = !inverse;
        } else {
          offset++;
        }
        hue = (hue + 1) % 256;
      }
      ledManager->fadeToBlack();
      break;
  }
}

void Random::mode(char letter) {
  Serial.print("Selected mode: ");
  Serial.println(letter);
  switch (letter) {
    case 'A': state = 0; offset = 0; break;
    case 'B': state = 1; offset = 0; strip = rand() % NUMBER_OF_LEDSTRIPS; hue = 0; inverse = false; break;
    default: break;
  }
}
