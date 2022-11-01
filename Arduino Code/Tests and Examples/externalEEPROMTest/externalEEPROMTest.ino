
#include <Wire.h>


#define ADDR_Ax 0b000 //A2, A1, A0
#define EEPROM_ADDRESS (0b1010 << 3) + ADDR_Ax


const int PA6 = 0;

const byte byteArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};


byte bufferArr[36];

void LightOn(){
  digitalWrite(PA6, HIGH);
}
void LightOff(){
  digitalWrite(PA6, LOW);
}

void flashLED(unsigned int numTimes){
  for(unsigned int i=0;i<numTimes;i++)
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
  for(int8_t i = 7; i>=0;i--)
  {
    ledDisplayNum(bitRead(b, i));
  }
}

void displayBytes(byte byteArr[], unsigned int arrSize)
{
  for(unsigned int i = 0; i<arrSize;i++)
  {
    displayByte(byteArr[i]);
  }
}



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(PA6, OUTPUT);
  LightOff();
  
  Wire.begin();  
 
  unsigned int dataAddress = 0;
 
//  bool success = writeEEPROM(EEPROM_ADDRESS, address, 0x87);

  bool success = writeEEPROM(EEPROM_ADDRESS, dataAddress, byteArr, sizeof(byteArr));
//  Serial.println(success);
  
  


//  byte readResult = 0x00;
//  readEEPROM(EEPROM_ADDRESS, dataAddress, readResult);
  
  readEEPROM(EEPROM_ADDRESS, dataAddress, bufferArr, sizeof(bufferArr));
  
//  displayBytes(bufferArr, sizeof(bufferArr));

for(int i=0;i<sizeof(bufferArr);i++)
{
  Serial.println(bufferArr[i]);
//  Serial.print(", ");
}

  

}

// the loop function runs over and over again forever
void loop() {

}


//////////////////////////////////////////////////////////////////////////////////////////////////////

bool writeEEPROM(int deviceaddress, unsigned int dataAddress, byte data[], unsigned int dataSize) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(dataAddress >> 8));   // MSB
  Wire.write((int)(dataAddress & 0xFF)); // LSB
  Wire.write(data, dataSize);
  bool result = Wire.endTransmission();
 
  delay(5);
  return result;
}

// readEEPROM(EEPROM_ADDRESS, dataAddress, bufferArr, sizeof(bufferArr));
void readEEPROM(int deviceaddress, uint8_t dataAddress, byte rdata[], int dataSize) 
{ 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(dataAddress >> 8));   // MSB
  Wire.write((int)(dataAddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,dataSize);
  
  for (unsigned int i = 0; i<dataSize; i++)
  {
    if (Wire.available()) 
    {
      bufferArr[i] = Wire.read();
    }
  }
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool writeEEPROM(int deviceaddress, unsigned int dataAddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(dataAddress >> 8));   // MSB
  Wire.write((int)(dataAddress & 0xFF)); // LSB
  Wire.write(data);
  bool result = Wire.endTransmission();
 
  delay(5);
  return result;
}
 
void readEEPROM(int deviceaddress, unsigned int dataAddress, byte& rdata ) 
{
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(dataAddress >> 8));   // MSB
  Wire.write((int)(dataAddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
}
