
//#ifdef MILLIS_USE_TIMERA0
//  #error "This sketch takes over TCA0 - please use a different timer for millis"
//#endif


//unsigned char quack_wav[] = {
//  0x7d, 0x7c, 0x7e, 0x7e, 0x7d, 0x7b, 0x7b, 0x7c, 0x7c, 0x7e, 0x7f, 0x7f,
//  0x81, 0x83, 0x84, 0x86, 0x88, 0x8a, 0x8b, 0x8c, 0x88, 0x7f, 0x76, 0x6f,
//  ...
//  0x82, 0x7f, 0x80
//};

unsigned int quack_wav_len = 1467;


uint8_t count = 40; //8 bit unsinged int
uint8_t DutyCycle = count/2; //8 bit unsinged int




void setup () {
  // Enable 64 MHz PLL and use as source for Timer1 ~~~ ATTiny402 has no PLL
//  PLLCSR = 1<<PCKE | 1<<PLLE;

 
// Set up Timer/Counter1 for PWM output ~~~ only need to setup 1 timer as i only connected 1 pin to the speaker

//16-bit Timer/Counter Type A (TCA) will control the pwm signal generation

    pinMode(PIN_PA6, OUTPUT);
//    takeOverTCB();
          
    
    // https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny202-402-AVR-MCU-with-Core-Independent-Peripherals_and-picoPower-40001969A.pdf#page=200
//    TCA0.SINGLE.CTRLB = 1<<CMP2EN| 1<<CMP1EN | 1<<CMP0EN | 0<<ALUPD | 0<<WGMODE;

    TCA0.SINGLE.CTRLA = 0b00001101; // enable the timer with prescaler 64
    
//    TCB0.CTRLA = 0x01; // enable the timer with no prescaler
      TCB0.CTRLA = 0b00000101; // enable the timer with 1024 prescaler, same as TCA0

//    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; // enable overflow interrupt


    TCB0.CTRLB = 0b00010111;

//    TCB0.CCMP = 0xFFFF;

    TCB0.CCMPL = count; // 255 counts
    TCB0.CCMPH = DutyCycle; // 50% duty cycle

    //perhaps equivalent to these:
//    TCA0.SINGLE.CMP0 = DutyCycle;
//    TCA0.SINGLE.PER = 0xFFFF;


    
    
//  TCCR1 = 1<<PWM1A | 2<<COM1A0 | 1<<CS10; // PWM A, clear on match, 1:1 prescale
//  GTCCR = 1<<PWM1B | 2<<COM1B0;           // PWM B, clear on match
//  OCR1A = 128; OCR1B = 128;               // 50% duty at start



  // Set up Timer/Counter0 for 8kHz interrupt to output samples.
  //for ATTiny402, use TCBn as a utility timer
//  TCCR0A = 3<<WGM00;                      // Fast PWM
//  TCCR0B = 1<<WGM02 | 2<<CS00;            // 1/8 prescale
//  TIMSK = 1<<OCIE0A;                      // Enable compare match
//  OCR0A = 124;                            // Divide by 1000

//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  pinMode(4, OUTPUT);
//  pinMode(1, OUTPUT);

//    pinMode(0, OUTPUT);
}

// Sample interrupt
//ISR (TIMER0_COMPA_vect) {
//  char sample = pgm_read_byte(&quack_wav[p++]);
//  OCR1A = sample; OCR1B = sample ^ 255;
//  // End of data? Go to sleep
//  if (p == quack_wav_len) {
//    adc_disable();
//    sleep_enable();
//    sleep_cpu();  // 1uA
//  }
//}
//
//ISR(TCA0_OVF_vect) { // on overflow, we will increment TCA0.CMP0, this will happen after every full cycle - a little over 7 minutes.
//  TCA0.SINGLE.CMP0 = DutyCycle++; // Because we are in Dual Slope Bottom mode, OVF fires at BOTTOM, at end, not TOP, in middle of the pulse.
//  TCB0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Always remember to clear the interrupt flags, otherwise the interrupt will fire continually!
//}

void loop(){
//  DutyCycle++;
//  TCB0.CCMPH = DutyCycle; // change duty cycle = change brightness
//  count++;
//  TCB0.CCMPL = count; 
//  delay(4);

  for (int i = 200; i>40;i--)
  {
    count = i;
    DutyCycle = count/2;
    
    TCB0.CCMPL = count;
    TCB0.CCMPH = DutyCycle;
    delay(10);
    
  }
  


//    count = 200;
//    DutyCycle = 100;
//    
//    TCB0.CCMPL = count;
//    TCB0.CCMPH = DutyCycle;
//
//    delay(250);
//    
//    count = 40;
//    DutyCycle = 20;
//    
//    TCB0.CCMPL = count;
//    TCB0.CCMPH = DutyCycle;
//
//    delay(250);
}
