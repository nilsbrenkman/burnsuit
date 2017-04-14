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
    case 2: doImplosionExplosion(); break;
    case 3: doGroupRainbow();       break;
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

void Master::rf(int senderId, int data1, int data2, int data3) {
  switch (program) {
    case 2:
      if (data1 == 0 && data2 == 1 && state == 1) {
        state = 0;
      }
      break;
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
    case 2:
      program = 2; // implosion/explosion
      state = 0;
      timeout = 0;
      offset = 0;
      color = 0;
      break;
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
  if (doEvent(200 * pow(2, speed))) {
    int myId = ledManager->getMyId();
    int color = offset;
    for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
      if (slavePresent[i]) {
        if (ledManager->sendToDevice(i, 1, 0, color)) {
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
    offset = (offset + 1) % 6;
  }
}

void Master::doImplosionExplosion() {
  switch (state) {
    case 0:
      if (slavePresent[offset]) {
        if (ledManager->sendToDevice(offset, 2, 0, color)) {
          state = 1;
          color = (color + 1) % 2;
          timeout = millis() + 10000; // wait 10 sec max
        }
      } else if (offset == ledManager->getMyId()) {
        offset = 0;
        state = 2;
        return;
      }
      offset = (offset + 1) % NUMBER_OF_DEVICES;
      break;
    case 1:
      if (doEvent(0)) {
        state = 0;
        offset = (offset + 1) % NUMBER_OF_DEVICES;
      }
      break;
    case 2:
      if (doEvent(50)) {
        if (ledManager->doProgramWithColorAndOffset(3, color, offset, true)) {
          state = 3;
          offset = 0;
          return;
        }
        offset++;
      }
      break;
    case 3:
      if (doEvent(50)) {
        if (ledManager->doProgramWithColorAndOffset(2, color, offset, true)) {
          state = 0;
          color = (color + 1) % 2;
          offset = (ledManager->getMyId() + 1) % NUMBER_OF_DEVICES;
          return;
        }
        offset++;
      }
      break;
    default: break;
  }
}
