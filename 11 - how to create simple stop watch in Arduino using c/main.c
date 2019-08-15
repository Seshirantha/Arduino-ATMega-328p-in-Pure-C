/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Create simple stop watch using Arduino in C programming language
*/

#include <avr/io.h>
#include <util/delay.h>

int count = 0;
int firstLightVal = 0;
int secondLightVal = 0;
int thirdLightVal = 0;
int fourthLightVal = 0;

// variable for reading the pin status
int stpRsumBtnVal;  

// variable to hold the button one state
int stpRsumBtnState;   

// variable to hold the number of presses
int stpRsumBtnPresses = 0;

// variable to hold the button two state
int resetBtnState = 0;

int main() {
  
  // initialize the four-seven segment display pin as an output
  DDRD = 0b11111100;//f,e,d,c,b,a
  DDRB = 0b111111;//d1,d2,d3,d4,h,g

  // initialize the pushbutton pin as an input
  DDRC = DDRC & 0b111100; // pin A1, A0, pin 1, 2 in block C

  stpRsumBtnState =  PINC & 0b000010;

  doContinously();

  return 0;
}

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

    // read input value and store it in stpRsumBtnVal
    stpRsumBtnVal = PINC & 0b000010;     

    // The button state has changed
    if (stpRsumBtnVal != stpRsumBtnState) {   
      // check if the button is pressed       
      if (stpRsumBtnVal == 0) {                
        stpRsumBtnPresses++;              
      }
    }

    stpRsumBtnState = stpRsumBtnVal;

    if (stpRsumBtnPresses % 2 == 1) {
      add(); // start
    } else if (stpRsumBtnPresses % 2 == 0) {
      // pause
    }

    // read input value and store it in buttonTwo state
    resetBtnState = PINC & 0b000001;

    // if reset button press, all the variables set to zero
    if (resetBtnState) {
      firstLightVal = 0;
      secondLightVal = 0;
      thirdLightVal = 0;
      fourthLightVal = 0;
    }


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
      PORTB |= 0b000100; //Light d1 up
      break;
    case 1:
      PORTB |= 0b001000; //Light d2 up
      break;
    case 2:
      PORTB |= 0b010000; //Light d3 up
      break;
    default:
      PORTB |= 0b100000; //Light d4 up
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
