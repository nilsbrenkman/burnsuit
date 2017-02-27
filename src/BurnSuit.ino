/*
* Project BurnSuit
* Description:
* Author:
* Date:
*/

#include "PCF8574_keypad.h"
#include "PCF8574_mombutt.h"
#include "AbstractProgram.h"
#include "Program1.h"
#include "Rainbow.h"
#include "ManualPulse.h"
#include "Sparkle.h"

AbstractProgram *program;
int LED = D7;

PCF8574_keypad controlpanel (D4, 0x27, ISR_controlpanel, 200, 100);
void ISR_controlpanel() { controlpanel.ISR(); } //wrapper function
PCF8574_mombutt sleevebuttons (D5, 0x20, ISR_sleevebuttons, 150, 50);
void ISR_sleevebuttons() { sleevebuttons.ISR(); } //wrapper function

void setup() {
  Serial.begin(9600);
  pinMode(D7, OUTPUT);
}

void loop() {
  doKeypad();
  doSleeveBoard();
  if (program != NULL) {
    program->loop();
  }
}

void doKeypad() {
  if (controlpanel.buttonpressed()) {
    int buttonid = controlpanel.getbutton();
    if (program != NULL) {
      program->clear();
      delete program;
    }
    switch (buttonid) {
      case 0: program = NULL;                   break;
      case 1: program = new Program1(500, LED); break;
      case 2: program = new Program1(200, LED); break;
      case 3: program = new Rainbow(5);         break;
      case 4: program = new ManualPulse();      break;
      case 5: program = new Sparkle();          break;
      default: break;
    }
    Serial.print("keypad button: ");
    Serial.println(buttonid);
  }
  controlpanel.updateinterrupt();
}

void doSleeveBoard() {
  if (sleevebuttons.buttonpressed()) {
    int buttonid = sleevebuttons.getbutton();
    if (program != NULL) {
      program->sleeve(buttonid);
    }
    Serial.print("sleeve button: ");
    Serial.println(buttonid);
  }
  sleevebuttons.updateinterrupt();
}
