#include "Master.h"

Master::Master(RF24 * r, int i) {
  radio = r;
  myId = i;
  Serial.println("Master active");
  numberOfSlaves = 0;
  for (int i = 0; i < ; i++) {
    slavePresent[i] = false;
  }
  timeout = 0;
  blink = true;
}

void Master::loop() {
  if (numberOfSlaves > 0 && timeout < millis()) {
    radio->stopListening();
    bool on = blink;
    for (int i = 0; i < ; i++) {
      if (slavePresent[i]) {
        radio->openWritingPipe(ADDRESSES[i]);
        unsigned long data_send = (unsigned long) 10;
        if (on) {
          data_send = (unsigned long) 11;
        }
        radio->write(&data_send, sizeof(unsigned long));
        on = ! on;
      }
    }
    timeout = millis() + 1000;
    blink = blink ? false : true;
    radio->startListening();
  }
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
  for (int i = 0; i < ; i++) {
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
