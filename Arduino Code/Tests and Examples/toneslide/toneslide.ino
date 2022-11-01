/* Example 3: High speed 8-bit PWM on PA3 on 8-pin part
 * https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/TakingOverTCA0.md
 * A user requested (#152) high speed PWM on PA3 on an 8-pin part. They wanted split mode
 * disabled, and PWM frequency higher than 62KHz. This is indeed possible - though do note
 * that the maximum frequency of PWM possible with a full 8 bits of resolution and 20MHz
 * system clock is 78.125 kHz (20000000/256) - and the next higher frequency for which
 * perfect 8-bit resolution is possible is half that, 39.061 kHz. Higher fequencies require
 * lower resolution (see above example for one approach, which can also be used for
 * intermediate frequencies) though if the frequency is constant, varying your input between
 * 0 and the period instead of using map() is desirable, as map may not be smooth. As a further
 * aside, if 78.125kHz is suitable, there is no need to disable split mode....
 */

#if defined(MILLIS_USE_TIMERA0) || !defined(__AVR_ATtinyxy2__)
  #error "This sketch is for an 8-pin part and takes over TCA0"
#endif

int duty;
int period;

void setup() {
  // We will be outputting PWM on PA3 on an 8-pin part
  pinMode(PIN_PA3, OUTPUT);                     // PA3 - TCA0 WO0, pin 4 on 8-pin parts
  PORTMUX.CTRLC     = PORTMUX_TCA00_DEFAULT_gc; // turn off PORTMUX, returning WO0 to PA3
  takeOverTCA0();                               // this replaces disabling and resettng the timer, required previously.
  TCA0.SINGLE.CTRLB = (TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc); // Single slope PWM mode, PWM on WO0

  TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm; // enable the timer with no prescaler

    duty = 30000;
    period = 60000;
    TCA0.SINGLE.PER = period;
    TCA0.SINGLE.CMP0 = duty; 
    delayMicroseconds(20);
}




void loop() { // Lets generate some output just to prove it works

//  duty = 30000;
//  period = 60000;
//  
//  for(int i = 30000; i > 12500; i--)
//  {
//    duty--;
//    period-=2;
//    TCA0.SINGLE.PER = period;
//    TCA0.SINGLE.CMP0 = duty; 
//    delayMicroseconds(20);
//  }

}
