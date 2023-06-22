#include <VarSpeedServo.h>
#include "Wire.h"  // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68;  // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z;  // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                             // variables for gyro raw data
int16_t temperature;                                        // variables for temperature data

char tmp_str[7];  // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) {  // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


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
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                  // PWR_MGMT_1 register
  Wire.write(0);                     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);                         // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false);              // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);  // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read();  // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read();  // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)


  if (accelerometer_x > 5000) {
    walk();
    delay(1000);
  } else if (accelerometer_y < -5000) {
    right_turn();
    delay(1000);
  } else if (accelerometer_y > 5000) {
    left_turn();
    delay(1000);
  }
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
