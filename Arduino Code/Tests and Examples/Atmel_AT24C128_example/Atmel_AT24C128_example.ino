#include <serialEEPROM.h>

/*
 * Atmel AT24C128 EEPROM Memory
 * Device Address 0x50 (A0 = GND, A1 = GND)
 * 128K bit memory = 16384 Bytes
 * 64-Byte Page Write Buffer
 */

serialEEPROM myEEPROM(0x50, 16384, 64);


const int PA6 = 0;

void LightOn(){
  digitalWrite(PA6, HIGH);
}
void LightOff(){
  digitalWrite(PA6, LOW);
}

void flashLED(unsigned int numTimes){
  for(int i=0;i<numTimes;i++)
  {
    LightOn();
    delay(20);
    LightOff();
    delay(20);
  }
}

void ledDisplayNum(byte b)
{

  if(b == 1)
  {
    //flash for 1 second)
    {
      flashLED(25);
    }
  }
  else
  {
    LightOn();
    delay(1000);
    LightOff();
  }
  delay(500);
}

void displayByte(byte b)
{
  for(uint8_t i; i<8;i++)
  {
    ledDisplayNum(bitRead(b, i));
  }
  
}




void setup()
{
  pinMode(PA6, OUTPUT);
  LightOff();
  flashLED(25);
  delay(2000);
	
	/* Write byte (Address 0x10) */
	myEEPROM.write(0x10, 0x87);

	/* Read byte (Address 0x10) */
	uint8_t num = 0x00;
	num = myEEPROM.read(0x10);
  displayByte(num);

	/* Write buffer (Address 0x30) */
//	const char* name = "Hello World!";
//	myEEPROM.write(0x30, (uint8_t*)name, strlen(name)+1);
//
//	/* Read buffer (Address 0x30) */
//	char aName[16] = {0};
//	myEEPROM.read(0x30, (uint8_t*)aName, sizeof(aName));
//	Serial.print("Read buffer: ");
//	Serial.println(aName);
}

void loop()
{
	delay(1000);
}
