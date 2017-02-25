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
    if (buttonid == 0) {
      program = NULL;
    } else if (buttonid == 1) {
      program = new Program1(500, LED);
    } else if (buttonid == 2) {
      program = new Program1(200, LED);
    } else if (buttonid == 3) {
      program = new Rainbow(5);
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
