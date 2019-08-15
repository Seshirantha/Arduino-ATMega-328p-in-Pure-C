/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Developing a knight rider application using C language for learning purpose.
*/



int main(void) {

  // DDR - Set to HIGH or LOW.
  // B - Digital pin from 8 to 13. (6s pins)
  // DDRB - Set digital pin from 8 to 13 as OUTPUTs.
  // PB0, PB1, PB2, PB3, PB4, PB4, PB6, PB6 in micorcontroller / pin 8,9,10,11,12,13 in arduino board.
  DDRB = 0b111111;

  // B - Digital pin from 8 to 13. (6s pins)
  // PORT - Set values to HIGH or LOW
  // PORTB - Digital pin from 8 to set HIGH.
  PORTB = 0b000001;

  // Number of lights.
  int numOfLights = 6;

  // Delay
  int delayTime = 50;

  while (1) {

    // Rotate to the right
    for (unsigned char i = 1; i < numOfLights; i++) {
      PORTB <<= 1;  
      _delay_ms(delayTime);
    }

    // Rotate to the left
    for (unsigned char i = 1; i < numOfLights; i++) {
      PORTB >>= 1;  
      _delay_ms(delayTime);
    }
  }
  return 0;
}
