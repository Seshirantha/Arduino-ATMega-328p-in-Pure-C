/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Controll Seven segments display using C
*/
byte num0 = 0x3F;
byte num1 = 0x6;
byte num2 = 0x5B;
byte num3 = 0x4F;
byte num4 = 0x66;
byte num5 = 0x6D;
byte num6 = 0x7C;
byte num7 = 0x7;
byte num8 = 0x7F;
byte num9 = 0x6F;

int main() {

  // Set output pins
  DDRD = 0b11111100; // Pin 2,3,4,5,6,7 from port D as outputs
  DDRB = 0b00000011; // Pin 8,9 from port B as outputs

  while (1) {
      
    // Each segment light on once. But human eye can't see it.
    onSegment(num0);
    onSegment(num1);
    onSegment(num2);
    onSegment(num3);
    onSegment(num4);
    onSegment(num5);
    onSegment(num6);
    onSegment(num7);
    onSegment(num8);
    onSegment(num9);
  }
  
  return 0;

}

// Get nth bit value
int getNthBit(int num, int n) {

  if (num & (1 << n)) {
    return 1;
  }
  else {
    return 0;
  }
}

// On related segments
void onSegment(byte num) {

  int result = getNthBit(num, 0); // Read Nth bit value
  
  if (result == 1) {
    PORTD = PORTD | 0b10000000;
  } else {
    PORTD = PORTD & 0b01111111;
  }

  result = getNthBit(num, 1);
  if (result == 1) {
    PORTD = PORTD | 0b01000000;
  } else {
    PORTD = PORTD & 0b10111111;
  }

  result = getNthBit(num, 2);
  if (result == 1) {
    PORTD = PORTD | 0b00010000;
  } else {
    PORTD = PORTD & 0b11101111;
  }

  result = getNthBit(num, 3);
  if (result == 1) {
    PORTD = PORTD | 0b00001000;
  } else {
    PORTD = PORTD & 0b11110111;
  }

  result = getNthBit(num, 4);
  if (result == 1) {
    PORTD = PORTD | 0b00000100;
  } else {
    PORTD = PORTD & 0b11111011;
  }

  result = getNthBit(num, 5);
  if (result == 1) {
    PORTB = PORTB | 0b000001;
  } else {
    PORTB = PORTB & 0b111110;
  }

  result = getNthBit(num, 6);
  if (result == 1) {
    PORTB = PORTB | 0b000010;
  } else {
    PORTB = PORTB & 0b111101;
  }

  _delay_ms(1000); // Delay for one second
}
