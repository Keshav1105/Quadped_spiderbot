#include <VarSpeedServo.h>

VarSpeedServo s1;
VarSpeedServo b1;
VarSpeedServo b2;
VarSpeedServo b3;
VarSpeedServo b4;
VarSpeedServo l1;
VarSpeedServo l2;
VarSpeedServo l3;
VarSpeedServo l4;
int trigpin = A4;
int echopin = A3;
int cm;
int duration;
int dl, dm, dr;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  s1.attach(10);
  b1.attach(3);
  l1.attach(2);
  b2.attach(4);
  l2.attach(5);
  b3.attach(7);
  l3.attach(6);
  b4.attach(8);
  l4.attach(9);
  stand();
  delay(1000);
}

void loop() {
  dm = us_read();
  if (dm < 10) {
    stand();
    s1.write(180, 100);
    delay(1000);
    dl = us_read();
    s1.write(0, 100);
    delay(1000);
    dr = us_read();
    if (dl > dr && dl > dm) {
      left_turn();
      stand();
    } else if (dr > dl && dr > dm) {
      right_turn();
      stand();
    }
    dm = us_read();
  }
  delay(1000);
  walk();
}

int us_read() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  duration = pulseIn(echopin, HIGH);
  cm = (duration / 29 / 2);
  delay(100);
  return (cm);
}
void stand() {
  s1.write(90, 100);
  b1.write(90, 100);
  b2.write(90, 100);
  b3.write(90, 100);
  b4.write(90, 100);

  l1.write(60, 100);
  l2.write(60, 100);
  l3.write(60, 100);
  l4.write(60, 100);
}

void walk() {
  l1.write(90, 100);
  l3.write(90, 100);
  delay(500);

  b1.write(140, 100);
  b3.write(40, 100);
  delay(500);

  l1.write(60, 100);
  l3.write(60, 100);
  delay(500);

  b1.write(90, 100);
  b3.write(90, 100);
  l2.write(90, 100);
  l4.write(90, 100);
  delay(500);

  b2.write(140, 100);
  b4.write(40, 100);
  delay(500);

  l2.write(60, 100);
  l4.write(60, 100);
  delay(500);

  b2.write(90, 100);
  b4.write(90, 100);
}

void left_turn() {
  l1.write(90, 100);
  l3.write(90, 100);
  delay(500);

  b1.write(40, 100);
  b3.write(40, 100);
  delay(500);

  l1.write(60, 100);
  l3.write(60, 100);
  delay(500);

  b1.write(90, 100);
  b3.write(90, 100);
  l2.write(90, 100);
  l4.write(90, 100);
  delay(500);

  b2.write(40, 100);
  b4.write(40, 100);
  delay(500);

  l2.write(60, 100);
  l4.write(60, 100);
  delay(500);

  b2.write(90, 100);
  b4.write(90, 100);
}

void right_turn() {
  l1.write(90, 100);
  l3.write(90, 100);
  delay(500);

  b1.write(140, 100);
  b3.write(140, 100);
  delay(500);

  l1.write(60, 100);
  l3.write(60, 100);
  delay(500);

  b1.write(90, 100);
  b3.write(90, 100);
  l2.write(90, 100);
  l4.write(90, 100);
  delay(500);

  b2.write(140, 100);
  b4.write(140, 100);
  delay(500);

  l2.write(60, 100);
  l4.write(60, 100);
  delay(500);

  b2.write(90, 100);
  b4.write(90, 100);
}
