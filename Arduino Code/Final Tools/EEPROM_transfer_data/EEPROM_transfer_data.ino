//
////000000000000000000000
//#include <Wire.h>
//#include <Streaming.h>
//#include "JC_EEPROM.h"
//
//
//
//#define ADDR_Ax 0b000 //A2, A1, A0
//#define EEPROM_ADDRESS (0b1010 << 3) + ADDR_Ax
//
//
//const int PA6 = 0;
//
//const byte byteArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
////const byte byteArr[] = {0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011};
//
//
//
//byte bufferArr[30];
//
//void LightOn(){
//  digitalWrite(PA6, HIGH);
//}
//void LightOff(){
//  digitalWrite(PA6, LOW);
//}
//
//void flashLED(unsigned int numTimes){
//  for(unsigned int i=0;i<numTimes;i++)
//  {
//    LightOn();
//    delay(20);
//    LightOff();
//    delay(20);
//  }
//}
//
//void ledDisplayNum(byte b)
//{
//
//  if(b == 1)
//  {
//    //flash for 0.4 second)
//    {
//      flashLED(10);
//    }
//  }
//  else
//  {
//    LightOn();
//    delay(400);
//    LightOff();
//  }
//  delay(200);
//}
//
//void displayByte(byte b)
//{
//  for(int8_t i = 7; i>=0;i--)
//  {
//    ledDisplayNum(bitRead(b, i));
//  }
//  delay(400);
//}
//
//void displayBytes(byte byteArr[], unsigned int arrSize)
//{
//  for(unsigned int i = 0; i<arrSize;i++)
//  {
//    displayByte(byteArr[i]);
//    
//  }
//}
//
//
//
//// Two 24LC256 EEPROMs on the bus
//JC_EEPROM eep(JC_EEPROM::kbits_128, 1, 64); // device size, number of devices, page size
//
//constexpr bool erase {false};               // true writes 0xFF to all addresses,
//                                            //   false performs write/read test
//constexpr uint32_t totalKBytes {16};        // for read and write test functions
//constexpr uint8_t btnStart {6};             // pin for start button
//
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//  // initialize digital pin LED_BUILTIN as an output.
////  pinMode(PA6, OUTPUT);
//
////  flashLED(100);
////  LightOff();
//
//  
//
//  
//
//  //initialize the new library
//  
//  uint8_t eepStatus = eep.begin(JC_EEPROM::twiClock400kHz);
////  eeErase(4, 0, totalKBytes * 1024 - 1);
////  LightOn();
//  
////  uint8_t values[4];
//
//  
////  displayBytes(values, 4);
//  
//
//  
////  Wire.begin();  
//// 
////  unsigned int dataAddress = 300;
//// 
////
////  writeEEPROM(EEPROM_ADDRESS, dataAddress, byteArr, 30);
////
////    
////  readEEPROM(EEPROM_ADDRESS, dataAddress, bufferArr, 30);
////
////  displayBytes(bufferArr, 30);
//
//
//}
//
//// the loop function runs over and over again forever
//void loop() {
//  dump(0, totalKBytes * 1024);    // dump everything
////  LightOff();
////  dump(0, totalKBytes * 1024);    // dump everything
////  LightOn();
//  
//}
//
//// write 0xFF to eeprom, "chunk" bytes at a time
//void eeErase(uint8_t chunk, uint32_t startAddr, uint32_t endAddr)
//{
//    chunk &= 0xFC;          // force chunk to be a multiple of 4
//    uint8_t data[chunk];
////    Serial << F("Erasing...") << endl;
//    for (int16_t i = 0; i < chunk; i++) data[i] = 0b10101010;
////    uint32_t msStart = millis();
//
//    for (uint32_t a = startAddr; a <= endAddr; a += chunk) {
////        if ( (a &0xFFF) == 0 ) Serial << a << endl;
//        eep.write(a, data, chunk);
//    }
////    uint32_t msLapse = millis() - msStart;
////    Serial << "Erase lapse: " << msLapse << " ms" << endl;
//}
//
//uint8_t d[16], last[16];
//
//void dump(uint32_t startAddr, uint32_t nBytes)
//{
//    Serial << endl << F("EEPROM DUMP 0x") << _HEX(startAddr) << F(" 0x") << _HEX(nBytes) << ' ' << startAddr << ' ' << nBytes << endl;
//    uint32_t nRows = (nBytes + 15) >> 4;
//
//    
//    uint32_t aLast {startAddr};
//    for (uint32_t r = 0; r < nRows; r++) {
//        uint32_t a = startAddr + 16 * r;
//        eep.read(a, d, 16); //uint8_t read(uint32_t addr, uint8_t* values, uint16_t nBytes);
//
//        bool same {true};
//        for (int i=0; i<16; ++i) {
//            if (last[i] != d[i]) same = false;
//        }
//        if (!same || r == 0 || r == nRows-1) {
//            Serial << "0x";
//            if ( a < 16 * 16 * 16 ) Serial << '0';
//            if ( a < 16 * 16 ) Serial << '0';
//            if ( a < 16 ) Serial << '0';
//            Serial << _HEX(a) << (a == aLast+16 || r == 0 ? "  " : "* ");
//            for ( int16_t c = 0; c < 16; c++ ) {
//                if ( d[c] < 16 ) Serial << '0';
//                Serial << _HEX( d[c] ) << ( c == 7 ? "  " : " " );
//            }
//            Serial << endl;
//            aLast = a;
//        }
//        for (int i=0; i<16; ++i) {
//            last[i] = d[i];
//        }
//    }
//}




















// Arduino JC_EEPROM Library
// https://github.com/JChristensen/JC_EEPROM
// Copyright (C) 2022 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to test JC_EEPROM library.
// Writes the EEPROM full of 32-bit integers and reads them back to verify.
// Wire a button from digital pin 6 to ground, this is used as a start button
// so the sketch doesn't do unnecessary EEPROM writes every time it's reset.
// Jack Christensen 09Jul2014

#include "JC_EEPROM.h"      // https://github.com/JChristensen/JC_EEPROM
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming
#include <Wire.h>           // https://arduino.cc/en/Reference/Wire
#include "Data.h"

// Two 24LC256 EEPROMs on the bus
JC_EEPROM eep(JC_EEPROM::kbits_128, 1, 64); // device size, number of devices, page size

constexpr bool erase {true};               // true writes 0xFF to all addresses,
                                            //   false performs write/read test
constexpr uint32_t totalKBytes {16};        // for read and write test functions
constexpr uint8_t btnStart {6};             // pin for start button

void setup()
{
    pinMode(btnStart, INPUT_PULLUP);
    Serial.begin(115200);
    Serial << F( "\n" __FILE__ "\n" __DATE__ " " __TIME__ "\n" );

    uint8_t eepStatus = eep.begin(JC_EEPROM::twiClock100kHz);   // go fast!
    if (eepStatus) {
        Serial << endl << F("extEEPROM.begin() failed, status = ") << eepStatus << endl;
        while (1);
    }

//    Serial << endl << F("Press button to start...") << endl;
//    while (digitalRead(btnStart) == HIGH) delay(10);    // wait for button push

    // chunkSize can be changed, but must be a multiple of 4 since we're writing 32-bit integers
    uint8_t chunkSize = 64;
    if (erase) {
        eeErase(chunkSize, 0, totalKBytes * 1024 - 1);
//        eep.write(0, rawData, sizeof(rawData));
        dump(0, totalKBytes * 1024);    // dump everything
    }

    Serial << "\nDone.\n";
}

void loop() {}

// write test data (32-bit integers) to eeprom, "chunk" bytes at a time
void eeWrite(uint8_t chunk)
{
    chunk &= 0xFC;          // force chunk to be a multiple of 4
    uint8_t data[chunk];
    uint32_t val = 0;
    Serial << F("Writing...") << endl;
    uint32_t msStart = millis();

    for (uint32_t addr = 0; addr < totalKBytes * 1024; addr += chunk) {
        if ( (addr &0xFFF) == 0 ) Serial << addr << endl;
        for (uint8_t c = 0; c < chunk; c += 4) {
            data[c+0] = val >> 24;
            data[c+1] = val >> 16;
            data[c+2] = val >> 8;
            data[c+3] = val;
            ++val;
        }
        eep.write(addr, data, chunk);
    }
    uint32_t msLapse = millis() - msStart;
    Serial << "Write lapse: " << msLapse << " ms" << endl;
}

// read test data (32-bit integers) from eeprom, "chunk" bytes at a time
void eeRead(uint8_t chunk)
{
    chunk &= 0xFC;          // force chunk to be a multiple of 4
    uint8_t data[chunk];
    uint32_t val = 0, testVal;
    Serial << F("Reading...") << endl;
    uint32_t msStart = millis();

    for (uint32_t addr = 0; addr < totalKBytes * 1024; addr += chunk) {
        if ( (addr &0xFFF) == 0 ) Serial << addr << endl;
        eep.read(addr, data, chunk);
        for (uint8_t c = 0; c < chunk; c += 4) {
            testVal =  ((uint32_t)data[c+0] << 24) + ((uint32_t)data[c+1] << 16) + ((uint32_t)data[c+2] << 8) + (uint32_t)data[c+3];
            if (testVal != val) Serial << F("Error @ addr ") << addr+c << F(" Expected ") << val << F(" Read ") << testVal << F(" 0x") << _HEX(testVal) << endl;
            ++val;
        }
    }
    uint32_t msLapse = millis() - msStart;
    Serial << "Last value: " << --val << " Read lapse: " << msLapse << " ms" << endl;
}

int dataAddr = 0;


// write 0xFF to eeprom, "chunk" bytes at a time
void eeErase(uint8_t chunk, uint32_t startAddr, uint32_t endAddr)
{
    
    
    chunk &= 0xFC;          // force chunk to be a multiple of 4
    uint8_t data[chunk];
    Serial << F("Erasing...") << endl;

    uint32_t msStart = millis();

    for (uint32_t a = startAddr; a <= endAddr; a += chunk) {
        for (int16_t i = 0; i < chunk; i++)
        {
          if(dataAddr>=13766)
          {
            data[i] = 0x00;
          }
          else
          {
            data[i] = pgm_read_word(rawData + dataAddr);
          }
          dataAddr++;
        }
        if ( (a &0xFFF) == 0 ) Serial << a << endl;
        eep.write(a, data, chunk);
    }
    uint32_t msLapse = millis() - msStart;
    Serial << "Erase lapse: " << msLapse << " ms" << endl;
}

// dump eeprom contents, 16 bytes at a time.
// always dumps a multiple of 16 bytes.
// duplicate rows are suppressed and indicated with an asterisk.
void dump(uint32_t startAddr, uint32_t nBytes)
{
    Serial << endl << F("EEPROM DUMP 0x") << _HEX(startAddr) << F(" 0x") << _HEX(nBytes) << ' ' << startAddr << ' ' << nBytes << endl;
    uint32_t nRows = (nBytes + 15) >> 4;

    uint8_t d[16], last[16];
    uint32_t aLast {startAddr};
    for (uint32_t r = 0; r < nRows; r++) {
        uint32_t a = startAddr + 16 * r;
        eep.read(a, d, 16);
        bool same {true};
        for (int i=0; i<16; ++i) {
            if (last[i] != d[i]) same = false;
        }
        if (!same || r == 0 || r == nRows-1) {
            Serial << "0x";
            if ( a < 16 * 16 * 16 ) Serial << '0';
            if ( a < 16 * 16 ) Serial << '0';
            if ( a < 16 ) Serial << '0';
            Serial << _HEX(a) << (a == aLast+16 || r == 0 ? "  " : "* ");
            for ( int16_t c = 0; c < 16; c++ ) {
                if ( d[c] < 16 ) Serial << '0';
                Serial << _HEX( d[c] ) << ( c == 7 ? "  " : " " );
            }
            Serial << endl;
            aLast = a;
        }
        for (int i=0; i<16; ++i) {
            last[i] = d[i];
        }
    }
}
