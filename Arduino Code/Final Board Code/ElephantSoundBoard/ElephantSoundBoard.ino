#include "data.h"
#include "JC_EEPROM.h"      // https://github.com/JChristensen/JC_EEPROM
#include <avr/sleep.h>

//#ifdef MILLIS_USE_TIMERA0
//  #error "This sketch takes over TCA0 - please use a different timer for millis"
//#endif

#define SAMPLE_ARR_SIZE 128

uint8_t samples[SAMPLE_ARR_SIZE];
uint8_t samples_size=SAMPLE_ARR_SIZE;

int sample_index = 0;



//read 16 bytes at a time

volatile uint8_t stored32Bytes[32] = {0x80, 0x80, 0x80, 0x81, 0x81, 0x80, 0x7E, 0x7E, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x81, 0x7F, 0x7E, 0x81, 0x80, 0x7C, 0x7C, 0x7E, 0x82, 0x7F, 0x7D, 0x81, 0x81, 0x80, 0x80, 0x81, 0x82, 0x7B, 0x7B};
volatile uint16_t storedByteIndex = 0; 

bool play=true;

const int TOTAL_SAMPLE_LENGTH = 13766;
//const int TOTAL_SAMPLE_LENGTH = 1798;




JC_EEPROM eep(JC_EEPROM::kbits_128, 1, 64); // device size, number of devices, page size


void setup () {
    uint8_t eepStatus = eep.begin(JC_EEPROM::twiClock400kHz);   // go fast!
    eep.read(0, stored32Bytes, 16);

     
    //16-bit Timer/Counter Type B (TCB0) will control the pwm signal generation

    pinMode(PIN_PA6, OUTPUT);
    TCB0.CTRLA = 0x01; // enable the timer with no prescaler
    TCB0.CTRLB = 0b00010111; //page 248
    TCB0.CCMPL = 255;
    TCB0.CCMPH = 255; 



    //Now setup the timer which fetches new values at 8 kHz
    // https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny202-402-AVR-MCU-with-Core-Independent-Peripherals_and-picoPower-40001969A.pdf#page=200

    pinMode(PIN_PA3, OUTPUT);                     // PA3 - TCA0 WO0, pin 4 on 8-pin parts
    PORTMUX.CTRLC     = PORTMUX_TCA00_DEFAULT_gc; // turn off PORTMUX, returning WO0 to PA3
    takeOverTCA0();                               // this replaces disabling and resettng the timer, required previously.
    TCA0.SINGLE.CTRLB = 0b00010011;
    TCA0.SINGLE.CTRLA = 0b00001001; // enable the timer with prescaler 16
    TCA0.SINGLE.PER = 150; //period register to make 6250 Hz sample rate
    TCA0.SINGLE.CMP0 = 75;
    TCA0.SINGLE.INTCTRL = 0b00010000; // enable compare interrupt

    
    //now set up the pin external interrupt
    // https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny202-402-AVR-MCU-with-Core-Independent-Peripherals_and-picoPower-40001969A.pdf#page=150
    
    PORTA.PIN7CTRL = 0x01;

    //other power optimizations
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    
    
    
}

bool risingEdge = false;
ISR(PORTA_PORT_vect) {
  risingEdge=!risingEdge;
  PORTA.INTFLAGS = PORT_INT7_bm;
  play = true;
}

int overallIndex = 16;

ISR(TCA0_CMP0_vect) { 


  
//  TCB0.CCMPH = samples[storedByteIndex++ & 0x1F]; 
  if(!risingEdge)
  {
    TCB0.CCMPH = 0x00;
    sleep_cpu();
    return;
  }
  else
  {
//    TCB0.CCMPH = hello_arr[storedByteIndex];
    TCB0.CCMPH = stored32Bytes[(storedByteIndex % 32)];
    storedByteIndex++;

    if(storedByteIndex>TOTAL_SAMPLE_LENGTH-2)
    {
      storedByteIndex = 0;
      overallIndex = 16;
      TCB0.CCMPH = 0x00;
      eep.read(0, stored32Bytes, 16);
      sleep_cpu();
    }

    if((storedByteIndex % 16) == 0)
    {
      if( (storedByteIndex % 32) == 0)
      {
        Wire.requestFrom(0x50, 16);
        for (byte i=16; i<32; i++) 
        {
          stored32Bytes[i] = Wire.read();
  //          stored32Bytes[i] = hello_arr[overallIndex];
  //          overallIndex++;
        }
      }
      else
      {
        Wire.requestFrom(0x50, 16);
        for (byte i=0; i<16; i++) 
        {
          stored32Bytes[i] = Wire.read();
  //          stored32Bytes[i] = hello_arr[overallIndex];
  //          overallIndex++;
            
        }
      }
  
  }
  


  



  }

  TCA0.SINGLE.INTFLAGS = 0b00010000; // Always remember to clear the interrupt flags, otherwise the interrupt will fire continually!

  
}


void loop(){

}
