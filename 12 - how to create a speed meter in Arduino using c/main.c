/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Create simple speed meter using Arduino in C programming language.
*/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define rs PB0    //pin8 
#define en PB1    //pin9

// Global variables
const int greenLimit = 20;
const int redLimit = 60;
int distance = 0;
int count = 1;
uint16_t timerValueInPosOne, timerValueInPosTwo;
float distanceForPositionOne = 0;
float distanceForPositionTwo = 0;
int movingSpeed = 0;
int devideFactor = 58;

void initVar() {
  /***********************************************Pins and ports for Ultra Module***************************************************/

  DDRC |= (1 << DDC4);
  DDRC = 0xFF;
  DDRC &= ~(1 << DDC5);
  PORTC |= (1 << PORTC5);
  PORTC &= ~(1 << PORTC4);
  PRR &= ~(1 << PRTIM1);
  TCNT1 = 0;
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << ICES1);
  PCICR = (1 << PCIE1);
  PCMSK1 = (1 << PCINT13);
  sei();

  /*******************************************Pins and port for LCD Display*****************************************/
  int i;
  DDRB = 0x00111111;
  DDRD = 0xF0;

}

/*******************************************functions for LCD Display*****************************************/
void start(){
  DDRB = 0x03;    // PB0 and PB1 declared as output
  DDRD = 0xF0;    // PD4,PD5,PD6,PD7 declared as output
  command(0x28);  // To initialize LCD in 2 lines, 5X8 dots and 4bit mode.
  command(0x0C);  // Display ON cursor OFF. E for cursor ON and C for cursor OFF
  command(0x06);  // Entry mode-increment cursor by 1
  command(0x01);  // Clear screen
  command(0x80);  // Sets cursor to (0,0)
}

// Basic function used in giving command
void command(char LcdCommand){ // to LCD
  char UpperHalf, LowerHalf;

  UpperHalf = LcdCommand & 0xF0;  // upper 4 bits of command
  PORTD &= 0x0F;                  // flushes upper half of PortD to 0, but retains lower half of PortD
  PORTD |= UpperHalf;
  PORTB &= ~(1 << rs);
  PORTB |= (1 << en);
  _delay_ms(10);
  PORTB &= ~(1 << en);
  _delay_ms(10);

  LowerHalf = ((LcdCommand << 4) & 0xF0); //lower 4 bits of command
  PORTD &= 0x0F;                  // flushes upper half of PortD to 0, but retains lower half of PortD
  PORTD |= LowerHalf;
  PORTB &= ~(1 << rs);
  PORTB |= (1 << en);
  _delay_ms(10);
  PORTB &= ~(1 << en);
  _delay_ms(10);
}

// Basic function used in giving data
void data(char AsciiChar){ // to LCD
  char UpperHalf, LowerHalf;

  UpperHalf = AsciiChar & 0xF0; // upper 4 bits of data
  PORTD &= 0x0F;       // flushes upper half of PortD to 0, but retains lower half of PortD
  PORTD |= UpperHalf;
  PORTB |= (1 << rs);
  PORTB |= (1 << en);
  _delay_ms(10);
  PORTB &= ~(1 << en);
  _delay_us(400);

  LowerHalf = ((AsciiChar << 4) & 0xF0); //lower 4 bits of data
  PORTD &= 0x0F;       // flushes upper half of PortD to 0, but retains lower half of PortD
  PORTD |= LowerHalf;
  PORTB |= (1 << rs);
  PORTB |= (1 << en);
  _delay_ms(10);
  PORTB &= ~(1 << en);
  _delay_us(400);
}

// Takes input a string and displays it
void sendAString(char *StringOfCharacters){ // max character in a string should be
  while (*StringOfCharacters > 0)          // less than 16, after 16th character
  { // everything will be ignored.
    data(*StringOfCharacters++);
  }
}

// Takes an integer as input and displays it
void sendAnInteger(int x){ // value of integer should be in between
  char buffer[20];         // the range of "int",
  itoa(x, buffer, 10);    //  else it'll print garbage values.
  sendAString(buffer);  // It use sendAString() for displaying.
}

// Clears the screen and
void clearScreen(){ // returns cursor to (0,0) position
  command(0x01);
}

/*******************************************functions for lights*****************************************/
void onLight(int dist){

  if (dist <= greenLimit) {
    PORTB = PORTB  & ~(1 << PORTB4 ) & ~(1 << PORTB5 ) | (1 << PORTB3 ) ;// On red light, when distance <= 20cm
  }
  if (greenLimit < dist && dist < redLimit) {
    PORTB = PORTB  & ~(1 << PORTB3 ) & ~(1 << PORTB5 ) | (1 << PORTB4 );// on blue light, when 20 < distance < 60cm
  }
  if (dist >= redLimit) {
    PORTB = PORTB  & ~(1 << PORTB4 ) & ~(1 << PORTB3 ) | (1 << PORTB5 ) ;// on green light, when distance >= 60cm
  }

}

int main(){

  initVar(); // initialize ports and pins

  /******************************************************Display*********************************************/
  _delay_ms(200);
  start(); // Start LCD
  sendAString("Speed meeter...!");

  _delay_ms(3000);

  while (1) {

    PORTC |= (1 << PC4); // trigger a wave
    _delay_us(10); // for 10uS
    PORTC &= ~(1 << PC4); // stop trigger
    
    clearScreen(); // clear screen
    sendAnInteger(movingSpeed); // print speed on CLD
    sendAString(" "); // print space on LCD
    sendAString("cm/s"); // print units in LCD

    onLight(distance); // on light
    _delay_ms (100);
  }
}

//**************************** interrupt service routing for untra module using port C**************************
ISR(PCINT1_vect) {

  if (bit_is_set(PINC, PC5)) {         // Checks if echo is high
    TCNT1 = 0;                // Reset Timer
  } else {
    uint16_t numOfuS = TCNT1;         // Save Timer value
    distance = numOfuS / devideFactor;

    // Save time and cal distance when position one
    if (count == 1) {
      timerValueInPosOne = TCNT1;
      distanceForPositionOne = timerValueInPosOne / devideFactor;
      count++;
    }
    // Save time and cal distance and speed when position two
    if (count == 2) {
      timerValueInPosTwo = TCNT1;
      distanceForPositionTwo = timerValueInPosTwo / devideFactor;
      
      movingSpeed = (distanceForPositionTwo - distanceForPositionOne) /
                    (timerValueInPosTwo - timerValueInPosOne) * 1000000;  // cm/s
      count--;
    }

    uint8_t oldSREG = SREG; // save current state
    cli();                  // Disable Global interrupts
    SREG = oldSREG;             // Enable interrupts

  }
}
