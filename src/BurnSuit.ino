/*
 * Project BurnSuit
 * Description:
 * Author:
 * Date:
 */

int T = 500;
int LED = D7;

void setup() {
  pinMode(D7, OUTPUT);
}


void loop() {
  int t = millis() % T;

  if (t < T/2) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
