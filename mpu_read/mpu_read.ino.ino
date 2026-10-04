#include <Wire.h>

const byte MPU_ADDR = 0x68;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1
  Wire.write(0);     // wake up
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, (byte)6);

  int16_t ax = (Wire.read() << 8) | Wire.read();
  int16_t ay = (Wire.read() << 8) | Wire.read();
  int16_t az = (Wire.read() << 8) | Wire.read();

  float angle = atan2((float)ax, (float)az) * 180.0 / PI;

  Serial.print("ax: "); Serial.print(ax);
  Serial.print("  az: "); Serial.print(az);
  Serial.print("  angle: "); Serial.println(angle);

  delay(50);
}