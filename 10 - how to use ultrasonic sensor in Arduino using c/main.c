/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Controll ultra sonic sensor using Arduino in C programming laguage
*/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


void init() {

  // Set 4th bit to one (OUTPUT) in DDRC register on pin PC4 to trigger
  DDRC |= (1 << DDC4);

  // Set 5th bit to zero (INPUT) in DDRC register on pin PC5
  DDRC &= ~(1 << DDC5);

  // Set 5th bit to one (HIGH) in PORTC register on pin PC5 to read Echo
  PORTC |= (1 << PORTC5);

  // Set 4th bit to zero (LOW) in PORTC register on pin PC4 to trigger
  PORTC &= ~(1 << PORTC4);

  // Set 7th bit to zero (Activate) in PRR register to activate the timer1 module
  PRR &= ~(1 << PRTIM1);

  // Timer/Counter register
  TCNT1 = 0;                // Initial timer value

  // Set 0th bit to one (No presacaler, timer clock = system clock) in Timer/Counter Control Register B
  // Since default clock for atmega328p is 1Mhz period is 1uS
  TCCR1B |= (1 << CS10);

  // Set 6th bit one in TCCR1B register to transfer contents in TCNT1 on the rising edge of the ICP pin
  TCCR1B |= (1 << ICES1);

  // Set zero bit to one in PCICR (Pin Change Interupt Controll Register) register
  // to enable PCINT[14:8] (Port C) pin to cause an interrup. Here, use pin C5 which is PCINT13
  PCICR = (1 << PCIE1);

  // Set 5th bit to one in  PCMSK1 (pin change mask 1) register
  // to Enable only PC5 interrupts
  PCMSK1 = (1 << PCINT13);

  // Enable Global Interrupts
  sei();                  
}


int main() {
  // Serial.begin(9600); // only for printing serial monitor value
  init();
  
  while (1) {
    // To allow sufficient time between queries (60ms min)
    _delay_ms(60);

    // Set 4th bit to one in PORTC register to trigger high
    PORTC |= (1 << PC4);

    // delay for 10 uS
    _delay_us(10);              // for 10uS

    // Set 4th bit to zero in PORTC register to trigger the ultra sinic module.
    PORTC &= ~(1 << PC4);
  }
}

// Interup service routing / interrupt handler for PCINT1 (Port C, PCINT8 - PCINT14) for pin C5
// When this interrupt occurs, the current program execution is stopped,
// the context is saved and the control jumps to Interrupt Service Routine (the ISR).
ISR(PCINT1_vect) {

  // Checks if echo is high
  if (bit_is_set(PINC, PC5)) {

    // Reset Timer
    TCNT1 = 0;

  } else {

    // Save Timer value
    uint16_t numuS = TCNT1;

    // Save status from the Status register.
    uint8_t oldSREG = SREG;

    // Disable Global interrupts
    cli();       

    // Enable interrupts
    SREG = oldSREG;
  }
}
