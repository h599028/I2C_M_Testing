/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"

#define I2C_DEV_ADDR 0x08
#define I2C_PGN_REQ 0x08



byte pgn_request = (byte)I2C_PGN_REQ;
int count = 0;

void setup()
{
	Wire.setPins(23, 22);
	Wire.begin();

	Serial.begin(115200);
	Serial.println("\nIIC Master");
}

void loop()
{

	Serial.println("\nIIC Master");

	byte inputByte[] = {0x08, 0x01, 0xf8, 0x02};
	int length;
	Wire.beginTransmission(I2C_DEV_ADDR);
	Wire.write(inputByte, 4);
	Wire.endTransmission();

	Wire.requestFrom(I2C_DEV_ADDR, 2);
	while (Wire.available())
	{
		int b1 = (int) Wire.read();
		int b2 = (int) Wire.read();

 		length = (b1 << 8) | b2;

		Serial.printf("Length : %d ", length );
		
	}

	Wire.requestFrom(I2C_DEV_ADDR, length);
	while (Wire.available()) {
		
		Serial.printf("%c", (char)Wire.read());
		
	}

	delay(5000);
}