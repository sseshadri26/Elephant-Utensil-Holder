unsigned char quack_wav[] = {
  0x7d, 0x7c, 0x7e, 0x7e, 0x7d, 0x7b, 0x7b, 0x7c, 0x7c, 0x7e, 0x7f, 0x7f,
  0x81, 0x83, 0x84, 0x86, 0x88, 0x8a, 0x8b, 0x8c, 0x88, 0x7f, 0x76, 0x6f,
  ...
  0x82, 0x7f, 0x80
};
unsigned int quack_wav_len = 1467;

void setup () {
  // Enable 64 MHz PLL and use as source for Timer1
  PLLCSR = 1<<PCKE | 1<<PLLE;     
 
  // Set up Timer/Counter1 for PWM output
  TIMSK = 0;                              // Timer interrupts OFF
  TCCR1 = 1<<PWM1A | 2<<COM1A0 | 1<<CS10; // PWM A, clear on match, 1:1 prescale
  GTCCR = 1<<PWM1B | 2<<COM1B0;           // PWM B, clear on match
  OCR1A = 128; OCR1B = 128;               // 50% duty at start

  // Set up Timer/Counter0 for 8kHz interrupt to output samples.
  TCCR0A = 3<<WGM00;                      // Fast PWM
  TCCR0B = 1<<WGM02 | 2<<CS00;            // 1/8 prescale
  TIMSK = 1<<OCIE0A;                      // Enable compare match
  OCR0A = 124;                            // Divide by 1000

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  pinMode(4, OUTPUT);
  pinMode(1, OUTPUT);
}

// Sample interrupt
ISR (TIMER0_COMPA_vect) {
  char sample = pgm_read_byte(&quack_wav[p++]);
  OCR1A = sample; OCR1B = sample ^ 255;
  // End of data? Go to sleep
  if (p == quack_wav_len) {
    adc_disable();
    sleep_enable();
    sleep_cpu();  // 1uA
  }
}
