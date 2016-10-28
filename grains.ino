/**
Date:     February 2015
Author:   Oscar Byrne
Project:  Granular synthesiser

References: 
  http://makezine.com/projects/make-35/advanced-arduino-sound-synthesis/
  http://tinkerit.googlecode.com/svn/trunk/Auduino/auduino.pde
  http://www.instructables.com/id/Arduino-Timer-Interrupts
  http://sphinx.mythic-beasts.com/~markt/ATmega-timers.html
**/

#define PWM_VALUE     OCR1A
#define PWM_INTERRUPT TIMER2_COMPA_vect

void setup() {
  Serial.begin(9600);
  
  cli(); //disable interrupts
 
  /** Set timer1 for 8-bit fast PWM output **/
  pinMode(9, OUTPUT);
  TCCR1A = 0;  // Clear control registers
  TCCR1B = 0;
  TCNT1  = 0;  // Clear counter value  
  TCCR1B |= (1 << CS10);   // Use no prescaler (16MHz increment)
  TCCR1A |= (1 << COM1A1); // Pin low when TCNT1=OCR1A
  TCCR1A |= (1 << WGM10);  // Use 8-bit fast PWM mode
  TCCR1B |= (1 << WGM12);
  
  /** Set timer2 interrupt at 25kHz **/
  TCCR2A = 0;  // Clear control registers
  TCCR2B = 0;
  TCNT2  = 0;  // Clear counter value
  TCCR2B |= (1 << CS22);   // Use 64 prescaler
  TCCR2A |= (1 << WGM21);  // Use CTC mode (counter clears on compare)
  TIMSK2 |= (1 << OCIE2A); // Enable timer compare interrupt
  OCR2A = 9;   // Set compare register for 25kHz = 16e6 / (25000*64) - 1
  
  sei(); //enable interrupts
}

/** Invoked by timer2 at SR of 25kHz **/
ISR(PWM_INTERRUPT) {
  if (Serial.available() > 0) {
    // read the incoming byte:
    PWM_VALUE = Serial.read();
  }
}

