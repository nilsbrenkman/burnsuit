#include "Master.h"

Master::Master(RF24 * r, int i) {
  radio = r;
  myId = i;
  Serial.println("Master active");
  numberOfSlaves = 0;
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    slavePresent[i] = false;
  }
}

void Master::loop() {
  // do nothing
}

void Master::clear() {
  // do nothing
}

void Master::sleeve(int buttonid) {
  // do nothing
}

void Master::mode(char letter) {
  switch (letter) {
    case 'A': registerSlaves(); break;
    default: break;
  }
}

void Master::registerSlaves() {
  numberOfSlaves = 0;
  radio->stopListening();
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    if (i != myId) {
      radio->openWritingPipe(ADDRESSES[i]);
      unsigned long data_send = (unsigned long) 1;
      if (radio->write(&data_send, sizeof(unsigned long))) {
        Serial.print("Device ");
        Serial.print(i);
        Serial.println(" is present!");
        numberOfSlaves++;
        slavePresent[i] = true;
      } else {
        Serial.print("Device ");
        Serial.print(i);
        Serial.println(" is NOT present :-(");
        slavePresent[i] = false;
      }
    } else {
      Serial.print("Device ");
      Serial.print(i);
      Serial.println(" is me, skipping");
      slavePresent[i] = false;
    }
  }
  Serial.print("Found ");
  Serial.print(numberOfSlaves);
  Serial.println(" slaves.");
  radio->startListening();
}
