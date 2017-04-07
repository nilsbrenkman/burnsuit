#include "Master.h"

Master::Master(RF24 * r, int i) {
  radio = r;
  myId = i;
  Serial.println("Master active");
  numberOfSlaves = 0;
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    slavePresent[i] = false;
  }
  int program = 0;
}

void Master::loop() {
  switch (program) {
    case 3: doGroupRainbow(); break;
    default: break;
  }
}

void Master::sleeve(int buttonid) {
  // do nothing
}

void Master::mode(char letter) {
  Serial.print("Selected mode: ");
  Serial.println(letter);
  switch (letter) {
    case 'A': registerSlaves(); break;
    default: break;
  }
}

bool Master::isMaster() {
  return true;
}

void Master::selectMasterMode(int buttonid) {
  Serial.print("Selected Master mode: ");
  Serial.println(buttonid);
  switch (buttonid) {
    case 3:
      program = 3; // group rainbow
      timeout = 0;
      offset = 0;
      break;
  }
}

void Master::registerSlaves() {
  numberOfSlaves = 0;
  radio->stopListening();
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    if (i != myId) {
      if (sendToDevice(i, (unsigned long) 1)) {
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

bool Master::sendToDevice(int id, unsigned long data) {
  radio->openWritingPipe(ADDRESSES[id]);
  /*unsigned long data_send = (unsigned long) 1;*/
  return radio->write(&data, sizeof(unsigned long));
}

void Master::doGroupRainbow() {
  if (timeout < millis()) {
    int color = offset;
    for(int i = 0; i < NUMBER_OF_DEVICES; i++) {
      if (slavePresent[i]) {
        unsigned long data = 100 + color; // 100 for program, color for offset
        if (sendToDevice(i, data)) {
          color = (color + 1) % 6;
        } else {
          Serial.print("Device ");
          Serial.print(i);
          Serial.println(" is no longer there.");
          slavePresent[i] = false;
          numberOfSlaves--;
        }
      } else if (i == myId) {
        ledManager->setAllLeds(color + 2);
        ledManager->show();
        color = (color + 1) % 6;
      }
    }
    timeout = millis() + 400;
    offset = (offset + 1) % 6;
  }
}
