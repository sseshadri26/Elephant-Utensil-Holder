/* Example 1: 16-bit PWM in single mode, dual slope with interrupt.
 * https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/TakingOverTCA0.md
 *
 * The whole "ISR adjusting duty cycle" like that probably isn't something you'd actually
 * want to do - but it demonstrates how to configure an ISR on TCA0, which is the point.
 */

#ifdef MILLIS_USE_TIMERA0
  #error "This sketch takes over TCA0 - please use a different timer for millis"
#endif

unsigned int DutyCycle = 50;


void setup() {
  // We will be outputting PWM on PB0
  pinMode(PIN_PA3, OUTPUT); // PB0 - TCA0 WO0, pin7 on 14-pin parts
  takeOverTCA0();                           // This replaces disabling and resettng the timer, required previously.
  TCA0.SINGLE.CTRLB = (TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_DSBOTTOM_gc); // Dual slope PWM mode OVF interrupt at BOTTOM, PWM on WO0
  TCA0.SINGLE.PER = 0xFFFF; // Count all the way up to 0xFFFF
  // At 20MHz, this gives ~152Hz PWM
  TCA0.SINGLE.CMP0 = DutyCycle;
  TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; // enable overflow interrupt
  TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm; // enable the timer with no prescaler
}

void loop() { // Not even going to do anything in here
}

ISR(TCA0_OVF_vect) { // on overflow, we will increment TCA0.CMP0, this will happen after every full cycle - a little over 7 minutes.
  TCA0.SINGLE.CMP0 = DutyCycle++; // Because we are in Dual Slope Bottom mode, OVF fires at BOTTOM, at end, not TOP, in middle of the pulse.
  TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Always remember to clear the interrupt flags, otherwise the interrupt will fire continually!
}
