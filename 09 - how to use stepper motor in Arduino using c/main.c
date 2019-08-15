/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Controll stepper motor using Arduino in C prgramming language
*/

#include <avr/io.h>
#include <util/delay.h>

int Steps = 0;
int Direction = 0;
int numberSteps = 512; // = 2018/4

void initial() {
  // Set 0,1,2,3 bits to one (INPUT) in DDRB register
  DDRB |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3);
}

void stepper(double numberOfSteps) {
  if (numberOfSteps >= 0) {
    Direction = 1;
  } else {
    Direction = 0;
    numberOfSteps = -numberOfSteps;
  }
  for (int x = 0; x < numberOfSteps * 8; x++) {
    switch (Steps) {
      case 0:
        PORTB = PORTB | (1 << PORTB3) & ~(1 << PORTB0) & ~(1 << PORTB1) & ~(1 << PORTB2);
        break;
      case 1:
        PORTB = PORTB & ~(1 << PORTB0) & ~(1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3);
        break;
      case 2:
        PORTB = PORTB & ~(1 << PORTB0) & ~(1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3);
        break;
      case 3:
        PORTB = PORTB & ~(1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1) & ~(1 << PORTB0);
        break;
      case 4:
        PORTB = PORTB & ~(1 << PORTB3) & ~(1 << PORTB2) | (1 << PORTB1) & ~(1 << PORTB0);
        break;
      case 5:
        PORTB = PORTB & ~(1 << PORTB3) & ~(1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0);
        break;
      case 6:
        PORTB = PORTB & ~(1 << PORTB3) & ~(1 << PORTB2) & ~(1 << PORTB1) | (1 << PORTB0);
        break;
      case 7:
        PORTB = PORTB | (1 << PORTB3) & ~(1 << PORTB2) & ~(1 << PORTB1)  | (1 << PORTB0);
        break;
      default:
        PORTB = PORTB & !(1 << PORTB3) & ~(1 << PORTB2) & ~(1 << PORTB1) & ~(1 << PORTB0);
        break;
    }

    _delay_ms(1);

    if (Direction == 1) {
      Steps++;
    }
    if (Direction == 0) {
      Steps--;
    }
    if (Steps > 7) {
      Steps = 0;
    }
    if (Steps < 0) {
      Steps = 7;
    }
  }
}

int main(void) {

  initial();
  while (1) {
    //1 rotation counter clockwise
    stepper(numberSteps);
    _delay_ms(1000);
    //1 rotation clockwise
    stepper(-numberSteps);
    _delay_ms(1000);
    //Keep track of step number
    for (int thisStep = 0; thisStep < numberSteps; thisStep++) {
      stepper(1);
    }
    _delay_ms(1000);
    for (int thisStep = numberSteps; thisStep > 0; thisStep--) {
      stepper(-1);
    }
    _delay_ms(1000);
  }
  return 0;
}
