#include "Master.h"

Master::Master() {
  Serial.println("Master active");
  numberOfSlaves = 0;
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    slavePresent[i] = false;
  }
  program = 0;
  speed = 2;
}

void Master::loop() {
  switch (program) {
    case 3: doGroupRainbow(); break;
    default: break;
  }
}

void Master::sleeve(int buttonid) {
  switch (buttonid) {
    case 0: speed = 0;                  break;
    case 1: if (speed > 0) { speed--; } break;
    case 2: if (speed < 4) { speed++; } break;
    default: break;
  }
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
      speed = 2;
      break;
  }
}

void Master::registerSlaves() {
  numberOfSlaves = 0;
  int myId = ledManager->getMyId();
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    if (i != myId) {
      if (ledManager->sendToDevice(i, 0, 0, 0)) {
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
}

void Master::doGroupRainbow() {
  if (timeout < millis()) {
    int myId = ledManager->getMyId();
    int color = offset;
    for(int i = 0; i < NUMBER_OF_DEVICES; i++) {
      if (slavePresent[i]) {
        if (ledManager->sendToDevice(i, 1, 1, color)) {
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
    timeout = millis() + (200 * pow(2, speed));
    offset = (offset + 1) % 6;
  }
}
