#include <Wire.h>
#include <Servo.h>

const byte MPU_ADDR = 0x68;
const byte SERVO_PIN = 10;

Servo servo;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  servo.attach(SERVO_PIN);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, (byte)6);

  int16_t ax = (Wire.read() << 8) | Wire.read();
  int16_t ay = (Wire.read() << 8) | Wire.read();
  int16_t az = (Wire.read() << 8) | Wire.read();

  float angle = atan2((float)ax, (float)az) * 180.0 / PI;

  // servo center is 90; counter-rotate against the tilt
  int target = constrain(90 - (int)angle, 0, 180);
  servo.write(target);

  Serial.print("ax: "); Serial.print(ax);
  Serial.print("  az: "); Serial.print(az);
  Serial.print("  angle: "); Serial.print(angle);
  Serial.print("  servo: "); Serial.println(target);

  delay(20);
}