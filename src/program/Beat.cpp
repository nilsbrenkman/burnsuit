#include "Beat.h"

Beat::Beat(MSGEQ7 * s) {
  Serial.println("Beat mode");
  sound = s;
  gain = 1;
  threshold = 1000;
  timeout = 0;
}

void Beat::loop() {
  if (doEvent(1000)) {
    sound->read();
    sound->process(gain, threshold);

    for (int i = 0; i < 7; i++) {
      Serial.print(sound->freqVolume[i]);
      Serial.print(", ");
    }
    Serial.println("");
  }
}

void Beat::sleeve(int buttonid) {

}
