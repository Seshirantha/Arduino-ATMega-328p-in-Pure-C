/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Control touch sensor using Arduino in C programming language.
*/
int main() {

  // PD3 as input and PD 7 as output
  DDRD = DDRD & ~(1 << PD3) | (1 << PD7);

  int sensorVal;

  while (1) {

    // Read sensor value
    sensorVal = PIND & (1 << PD3);

    // if pressed
    if (sensorVal == 8 )
    {
      // Set PD7 HIGH
      PORTD = PORTD | (1 << PD7);
    } else {
      // Set PD7 LOW
      PORTD = PORTD & (0 << PD7);
    }
  }
