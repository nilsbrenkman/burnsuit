#include <math.h>
#include "PCF8574_keypad.h"
#include "PCF8574_mombutt.h"
#include "afrored.h"
#include "particle-rf24.h"
#include "Constants.h"
#include "LedManager.h"
#include "AbstractLedStrip.h"
#include "LedStripL1.h"
#include "AbstractProgram.h"
#include "Program1.h"
#include "Rainbow.h"
#include "ManualPulse.h"
#include "Sparkle.h"
#include "Master.h"
#include "Slave.h"

AbstractProgram * program;
LedManager * ledManager;

const int PIN_IR_RECEIVER = D7;
const int PIN_IR_LED      = D2;
const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int ir_cooldown     = 100;
int myId;
int time_last_irmsg = 0;

PCF8574_keypad controlpanel(D4, 0x27, ISR_controlpanel, 200, 100);
void ISR_controlpanel() { controlpanel.ISR(); }   // wrapper function
PCF8574_mombutt sleevebuttons (D5, 0x20, ISR_sleevebuttons, 150, 50);
void ISR_sleevebuttons() { sleevebuttons.ISR(); } // wrapper function
afrored infrared(IR_MSG_LENGTH, IR_CARRIER_FREQ);
void ISR_infrared() { infrared.ISR(); }
RF24 radio(A6, A2);

void setup() {
  Serial.begin(9600);
  String deviceId = System.deviceID();
  Serial.print("My id: ");
  Serial.println(deviceId);
  for (int i = 0; i < NUMBER_OF_DEVICES; i++) {
    if (DEVICEIDS[i] == deviceId) {
      myId = i;
    }
  }

  ledManager = new LedManager(&radio, myId);
  AbstractLedStrip * ledStrip;
  ledStrip = new AbstractLedStrip(0, 2, true,  true,  1);
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(0, ledStrip);
  ledStrip = new AbstractLedStrip(2, 2, false, false, 2);
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(1, ledStrip);
  /*
  ledStrip = new AbstractLedStrip(0,   24, false, false, 1);  // R1
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(0, ledStrip);
  ledStrip = new AbstractLedStrip(24,  38, true,  false, 2);  // R2
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(1, ledStrip);
  ledStrip = new AbstractLedStrip(62,  25, true,  false, 0);  // RS
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(2, ledStrip);
  ledStrip = new AbstractLedStrip(87,  20, true,  false, 3);  // R3
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(3, ledStrip);
  ledStrip = new AbstractLedStrip(107, 20, false, false, 4);  // R4
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(4, ledStrip);
  ledStrip = new AbstractLedStrip(127, 20, true,  true,  4);  // L4
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(5, ledStrip);
  ledStrip = new AbstractLedStrip(147, 20, false, true,  3);  // L3
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(6, ledStrip);
  ledStrip = new AbstractLedStrip(167, 24, true,  true,  1);  // L1
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(7, ledStrip);
  ledStrip = new AbstractLedStrip(189, 38, false, true,  2);  // L2
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(8, ledStrip);
  ledStrip = new AbstractLedStrip(229, 25, true,  true,  0);  // LS
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(9, ledStrip);
  */

  attachInterrupt(PIN_IR_RECEIVER, ISR_infrared, CHANGE);
  infrared.attachreceiver(PIN_IR_RECEIVER, ISR_infrared);
  infrared.attachtransmitter(PIN_IR_LED);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(ADDRESSES[myId]);
  radio.openReadingPipe(1, ADDRESSES[myId]);
  radio.startListening();
}

void loop() {
  doKeypad();
  doSleeveBoard();
  doInfraredReceive();
  /*doSerialRead();*/
  doRfReceive();
  if (program != NULL) {
    program->loop();
  }
}

void doKeypad() {
  if (controlpanel.buttonpressed()) {
    int buttonid = controlpanel.getbutton();
    switch (buttonid) {
      case 12:  if (program != NULL) { program->mode('A'); } return;
      case 13:  if (program != NULL) { program->mode('B'); } return;
      case 14:  if (program != NULL) { program->mode('C'); } return;
      case 15:  if (program != NULL) { program->mode('D'); } return;
      default: break;
    }
    if (program != NULL) {
      if (program->isMaster() && buttonid != 0) {
        program->selectMasterMode(buttonid);
        return;
      }
      program->clear();
      delete program;
    }
    switch (buttonid) {
      case 0: program = NULL;                      break;
      case 1: program = new Master();              break;
      /*case 2: program = new Program1(200, LED); break;*/
      case 3: program = new Rainbow();             break;
      case 4: program = new ManualPulse();         break;
      case 5: program = new Sparkle();             break;
      default: break;
    }
    if (program != NULL) {
      program->init(ledManager);
    }
    /*Serial.print("keypad button: ");
    Serial.println(buttonid);*/
  }
  controlpanel.updateinterrupt();
}

void doSleeveBoard() {
  if (sleevebuttons.buttonpressed()) {
    int buttonid = sleevebuttons.getbutton();
    switch (buttonid) {
      case 5: ledManager->setBrightnessPersistent(5, false); break;
      case 6: ledManager->setBrightnessPersistent(1, true);  break;
      case 7: ledManager->setBrightnessPersistent(-1, true); break;
      default:
        if (program != NULL) {
          program->sleeve(buttonid);
        }
        break;
    }
    infrared.sendmsg(buttonid);
    /*Serial.print("sleeve button: ");
    Serial.println(buttonid);*/
  }
  sleevebuttons.updateinterrupt();
}

void doInfraredReceive() {
  if (infrared.isnewmsg) {
    if (infrared.checkmsg()) {
      int data = infrared.getmsg();
      if (program != NULL) {
        program->infrared(data);
      }
      Serial.print("Infrared in: ");
      Serial.println(data);
      time_last_irmsg = millis();
    }
  }
  if (millis() > time_last_irmsg + ir_cooldown) {
    attachInterrupt(PIN_IR_RECEIVER, ISR_infrared, CHANGE);
  }
}

void doRfReceive() {
  if (radio.available()) {
    unsigned long data;
    while (radio.available()) {
      radio.read(&data, sizeof(unsigned long));
    }
    Serial.println(data);
    int senderId = (data & 0xff000000) >> 24;
    int data1 =    (data & 0x00ff0000) >> 16;
    int data2 =    (data & 0x0000ff00) >>  8;
    int data3 =    (data & 0x000000ff)      ;
    if (data1 == 0 && data2 == 0) {             // enter slave mode
      if (program != NULL) {
        program->clear();
        delete program;
      }
      program = new Slave();
      program->init(ledManager);
      return;
    }
    if (program != NULL) {
      program->rf(senderId, data1, data2, data3);
    }
  }
}

void doSerialRead() {
  if (Serial.available() > 0) {
    int received = 0;
    while (Serial.available() > 0) {
      int byte = Serial.read();
      if (byte != 10) {
        received = (received * 10) + byte - 48;
      }
    }
    Serial.print("Serial read: ");
    Serial.println(received);
    if (program != NULL) {
      program->infrared(received);
    }
  }
}
