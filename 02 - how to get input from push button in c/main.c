/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Read inputs using C
*/

int buttonState = 0;

int main() {

   // Initialize the LED pin as an output:
  DDRB = DDRB | 0b100000; // pin 13 

  // Initialize the pushbutton pin as an input:
  DDRC = DDRC & 0b111101; // pin A1
  
  while(1){
      
      // Cead the state of the pushbutton value
      buttonState = PINC & 0b000010;
      
      // Check if the pushbutton is pressed.
      if (buttonState) {
        PORTB = PORTB | 0b100000; // Turn LED on
      } else {
        PORTB = PORTB & 0b011111; // Turn LED off:
      }
  }
  return 0;
}
