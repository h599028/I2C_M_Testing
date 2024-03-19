/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
#include <Arduino.h>
#include <Wire.h>

#define I2C_DEV_ADDR 0x42

int count = 0;

void requestByte(byte myIndex)
{
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(myIndex);
  Wire.endTransmission();

  Wire.requestFrom(I2C_DEV_ADDR, 1);
  while (Wire.available())
  {
    byte b1 = Wire.read();
    // byte b2=Wire.read();
    Serial.printf("%u", b1);
  }

}

void setup()
{
  Wire.setPins(23, 22);
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nIIC Master");
}

void loop()
{
  if (count <8) {
    Serial.printf("%u\n",count);
    requestByte(count);
    Serial.printf("\n");
    count++;
  }

  delay(5000);
}