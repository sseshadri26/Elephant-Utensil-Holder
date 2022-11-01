//
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//bool writeEEPROM(int deviceaddress, unsigned int dataAddress, byte data[], unsigned int dataSize) 
//{
//  Wire.beginTransmission(deviceaddress);
//  Wire.write( static_cast<uint8_t> (dataAddress >> 8));   // MSB
//  Wire.write( static_cast<uint8_t> (dataAddress & 0xFF)); // LSB
//  Wire.write(data, dataSize);
//  bool result = Wire.endTransmission();
// 
//  delay(5);
//  return result;
//}
//
//// readEEPROM(EEPROM_ADDRESS, dataAddress, bufferArr, sizeof(bufferArr));
//void readEEPROM(int deviceaddress, uint8_t dataAddress, byte rdata[], int dataSize) 
//{ 
//  Wire.beginTransmission(deviceaddress);
//  Wire.write( static_cast<uint8_t> (dataAddress >> 8));   // MSB
//  Wire.write( static_cast<uint8_t> (dataAddress & 0xFF)); // LSB
//  Wire.endTransmission();
// 
//  Wire.requestFrom(deviceaddress,dataSize);
//  
//  for (unsigned int i = 0; i<dataSize; i++)
//  {
//    if (Wire.available()) 
//    {
//      bufferArr[i] = Wire.read();
//    }
//  }
//}
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool writeEEPROM(int deviceaddress, unsigned int dataAddress, byte data ) 
//{
//  Wire.beginTransmission(deviceaddress);
//  Wire.write( static_cast<uint8_t> (dataAddress >> 8));   // MSB
//  Wire.write( static_cast<uint8_t> (dataAddress & 0xFF)); // LSB
//  Wire.write(data);
//  bool result = Wire.endTransmission();
// 
//  delay(5);
//  return result;
//}
// 
//void readEEPROM(int deviceaddress, unsigned int dataAddress, byte& rdata ) 
//{
// 
//  Wire.beginTransmission(deviceaddress);
//  Wire.write( static_cast<uint8_t> (dataAddress >> 8));   // MSB
//  Wire.write( static_cast<uint8_t> (dataAddress & 0xFF)); // LSB
//  Wire.endTransmission();
// 
//  Wire.requestFrom(deviceaddress,1);
// 
//  if (Wire.available()) rdata = Wire.read();
// 
//}
