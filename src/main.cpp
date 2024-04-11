/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"

#define I2C_DEV_ADDR 0x08

BluetoothSerial SerialBT;

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
  SerialBT.begin();

  Serial.println("\nIIC Master");
  SerialBT.println("\nIIC Master (BT)");

  
}

void loop()
{
  if (SerialBT.available())
  {
    byte inputByte = (byte)SerialBT.read();

    Wire.beginTransmission(I2C_DEV_ADDR);
    Wire.write(inputByte);
    Wire.endTransmission();

    Wire.requestFrom(I2C_DEV_ADDR, 1);
    while (Wire.available())
    {
      byte b1 = Wire.read();
      // byte b2=Wire.read();
      SerialBT.printf("\n" + b1);
    }
  }
  if (count <8) {
    Serial.printf("%u\n",count);
    requestByte(count);
    Serial.printf("\n");
    count++;
  }

  delay(5000);
}