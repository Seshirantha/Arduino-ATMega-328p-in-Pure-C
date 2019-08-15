/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Controll four seven segment display using Arduino in C programming langugae
*/

#include <avr/io.h>
#include <util/delay.h>

int count = 0;
int firstLightVal = 0;
int secondLightVal = 0;
int thirdLightVal = 0;
int fourthLightVal = 0;

int main() {
 
  // initialize the four-seven segment display pin as an output
  DDRD = 0b11111100;//f,e,d,c,b,a
  DDRB = 0b111111;//d1,d2,d3,d4,point,g

  doContinously();

  return 0;
}

// callback for helperThread
void add() {

  count ++;
  if (count == 50) {
    count = 0;
    firstLightVal++;
    if (firstLightVal == 10) {
      firstLightVal = 0;
      secondLightVal++;
      if (secondLightVal == 6) {
        secondLightVal = 0;
        thirdLightVal++;
        if (thirdLightVal == 10) {
          thirdLightVal = 0;
          fourthLightVal++;
          if (fourthLightVal == 6) {
            fourthLightVal = 0;
          }
        }
      }

    }
  }
}

// do forever
void doContinously() {

  while (1) {

    add();

    clearLEDs();// clear the 7-segment display screen
    pickDigit(0);// Light up 7-segment display d1
    pickNumber(fourthLightVal); // get the value of thousand
    _delay_ms(5);// delay 5ms

    clearLEDs();// clear the 7-segment display screen
    pickDigit(1);// Light up 7-segment display d2
    pickNumber(thirdLightVal); // get the value of hundred
    _delay_ms(5);// delay 5ms

    clearLEDs();// clear the 7-segment display screen
    pickDigit(2);// Light up 7-segment display d3
    pickNumber(secondLightVal); //get the value of ten
    _delay_ms(5);// delay 5ms

    clearLEDs();// clear the 7-segment display screen
    pickDigit(3);// Light up 7-segment display d4
    pickNumber(firstLightVal); //Get the value of single digit
    _delay_ms(5);// delay 5ms

  }
}

//light up a 7-segment display
void pickDigit(int x) {

  PORTB &= 0b111011; //(d4, LOW);
  PORTB &= 0b110111; // (d3, LOW);
  PORTB &=  0b101111; // (d2, LOW);
  PORTB &= 0b011111; // (d1, LOW);

   switch (x)
  {
    case 0:
      PORTB = PORTB | 0b000100 | 0b000010; //Light d1 up or Light off first decimal point
      break;
    case 1:
      PORTB = PORTB | 0b001000 | 0b00010; //Light d2 up or Light on second decimal point
      break;
    case 2:
      PORTB = PORTB | 0b010000 | 0b000010; //Light d3 up or Light off third decimal point
      break;
    default:
      PORTB = PORTB | 0b100000 | 0b000010; //Light d4 up or Light off fourth decimal point
      break;
  }
}

void pickNumber(int x) {
  switch (x)
  {
    default:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
}

//clear the 7-segment display screen
void clearLEDs() {

  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD &= 0b10111111; // (e, LOW)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
  PORTB &= 0b111101;   // (p, LOW)
}

//the 7-segment led display 0
void zero() {

  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD &= 0b10111111; // (e, LOW)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB |= 0b000001;   // (g, HIGH)
}

//the 7-segment led display 1
void one() {

  PORTD |= 0b00000100; // (a, HIGH)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD |= 0b00100000; // (d, HIGH)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD |= 0b10000000; // (f, HIGH)
  PORTB |= 0b000001;   // (g, HIGH)
}

//the 7-segment led display 2
void two() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD |= 0b00010000; // (c, HIGH)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD &= 0b10111111; // (e, LOW)
  PORTD |= 0b10000000; // (f, HIGH)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 3
void three() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD |= 0b10000000; // (f, HIGH)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 4
void four() {
  PORTD |= 0b00000100; // (a, HIGH)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD |= 0b00100000; // (d, HIGH)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 5
void five() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD |= 0b00001000; // (b, HIGH)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 6
void six() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD |= 0b00001000; // (b, HIGH)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD &= 0b10111111; // (e, LOW)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 7
void seven() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD |= 0b00100000; // (d, HIGH)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD |= 0b10000000; // (f, HIGH)
  PORTB |= 0b000001;   // (g, HIGH)
}

//the 7-segment led display 8
void eight() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD &= 0b10111111; // (e, LOW)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
}

//the 7-segment led display 9
void nine() {
  PORTD &= 0b11111011; // (a, LOW)
  PORTD &= 0b11110111; // (b, LOW)
  PORTD &= 0b11101111; // (c, LOW)
  PORTD &= 0b11011111; // (d, LOW)
  PORTD |= 0b01000000; // (e, HIGH)
  PORTD &= 0b01111111; // (f, LOW)
  PORTB &= 0b111110;   // (g, LOW)
}
