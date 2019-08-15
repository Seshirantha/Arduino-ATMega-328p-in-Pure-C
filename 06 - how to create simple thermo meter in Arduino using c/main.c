/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Create digital thermo meter using Arduin in C programming language.
*/

#include <avr/io.h>
#include <util/delay.h>

const int inPin = 0; //Middle (Output) pin of LM35
float temperature;

//light up a 7-segment display
void pickDigit(int x) {

 // (d4, LOW), (d3, LOW), (d2, LOW), (d1, LOW)
  PORTB = PORTB & 0b111011 & 0b110111 & 0b101111 & 0b011111;

  switch (x)
  {
    case 0:
      PORTB = PORTB | 0b000100 | 0b000010; //Light d1 up or Light off first decimal point
      break;
    case 1:
      PORTB = PORTB | 0b001000 | 0b00000; //Light d2 up or Light on second decimal point
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
    case 10:
      celcius();
      break;
  }
}

// Print "c" in the seven segment display
void celcius() {
// (a, LOW), (b, HIGH), (c, HIGH), (d, LOW), (e, LOW), (f, LOW)
  PORTD = PORTD & 0b11111011 | 0b00001000 | 0b00010000 & 0b11011111 & 0b10111111 & 0b01111111; 
// (g, HIGH)
  PORTB |= 0b000001;   
}

//clear the 7-segment display screen
void clearLEDs() {
// (a, LOW), (b, LOW), (c, LOW), (d, LOW), (e, LOW), (f, LOW)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11101111 & 0b11011111 & 0b10111111 & 0b01111111; 
// (g, LOW), (p, LOW)
  PORTB = PORTB & 0b111110 & 0b111101;   
}

//the 7-segment led display 0
void zero() {
// (a, LOW), (b, LOW), (c, LOW), (d, LOW), (e, LOW), (f, LOW), (g, HIGH)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11101111 & 0b11011111 & 0b10111111 & 0b01111111; 
// (g, LOW) 
  PORTB |= 0b000001;    

}

//the 7-segment led display 1
void one() {
// (a, HIGH), (b, LOW), (c, LOW), (d, HIGH), (e, HIGH), (f, HIGH)
  PORTD = PORTD | 0b00000100 & 0b11110111 & 0b11101111 | 0b00100000 | 0b01000000 | 0b10000000; 
 // (g, HIGH)
  PORTB |= 0b000001;   

}

//the 7-segment led display 2
void two() {
	// (a, LOW), (b, LOW), (c, HIGH), (d, LOW), (e, LOW), (f, HIGH)
  PORTD = PORTD &  0b11111011 & 0b11110111 | 0b00010000 & 0b11011111 & 0b10111111 | 0b10000000; 
  // (g, LOW)
  PORTB &= 0b111110;   
}

//the 7-segment led display 3
void three() {
	// (a, LOW), (b, LOW), (c, LOW),  (d, LOW), (e, HIGH),  (f, HIGH)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11011111 | 0b01000000 | 0b10000000; 
// (g, LOW)
  PORTB &= 0b111110;   
}

//the 7-segment led display 4
void four() {
	// (a, HIGH), (b, LOW), (c, LOW), (d, HIGH), (e, HIGH), (f, LOW)
  PORTD = PORTD | 0b00000100 & 0b11110111 & 0b11101111 | 0b00100000 | 0b01000000 & 0b01111111; 
  // (g, LOW)
  PORTB &= 0b111110;  
}

//the 7-segment led display 5
void five() {
	// (a, LOW), (b, HIGH), (c, LOW), (d, LOW), (e, HIGH), (f, LOW), 
  PORTD = PORTD & 0b11111011 | 0b00001000 & 0b11101111 & 0b11011111 | 0b01000000 & 0b01111111; 
 // (g, LOW)
  PORTB &= 0b111110;   
}

//the 7-segment led display 6
void six() {
	// (a, LOW), (b, HIGH), (c, LOW), (d, LOW),  (e, LOW), (f, LOW), 
  PORTD = PORTD & 0b11111011 | 0b00001000 & 0b11101111 & 0b11011111 & 0b10111111 & 0b01111111; 
// (g, LOW)
  PORTB &= 0b111110; 
}

//the 7-segment led display 7
void seven() {
	// (a, LOW), // (b, LOW), (c, LOW),  (d, HIGH),  (e, HIGH), (f, HIGH)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11101111 | 0b00100000 | 0b01000000 | 0b10000000; 
// (g, HIGH)
  PORTB |= 0b000001;   
}

//the 7-segment led display 8
void eight() {
  //// (a, LOW), (b, LOW), (c, LOW), (d, LOW), (e, LOW), (f, LOW)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11011111 & 0b10111111 & 0b01111111; // (a, LOW)
  // (g, LOW)
  PORTB &= 0b111110; 
}

//the 7-segment led display 9
void nine() {
  // (a, LOW), (b, LOW), (c, LOW), (d, LOW), (e, HIGH), (f, LOW)
  PORTD = PORTD & 0b11111011 & 0b11110111 & 0b11101111 & 0b11011111 | 0b01000000 & 0b01111111; // (a, LOW)
  // (g, LOW)
  PORTB &= 0b111110;   
}

// 
void InitADC()
{
  //  16Mhz / 128 = 125kHz ADC reference clock. (On the other hand set prescaller to 128)
  //  ny setting 0, 1 and second bits of ADCSRA register to digital one.
  ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
  // Voltage reference from AVcc (5V on ATMega328p) by setting the 6th bit of the ADMUX register to digital one.
  ADMUX |= (1 << REFS0);
  // Turn on ADC by setting 6th bit of the ADCSRA to digital one.
  ADCSRA |= (1 << ADEN);
  // Do a preliminary conversion by setting 6th bit of the ADCSRA register.
  ADCSRA |= (1 << ADSC);
}

unsigned int ADC_Read(unsigned char channel)
{
  //Clear previously read channels
  ADMUX = ADMUX & 0b11110000;
  //Define new ADC Channel to read (which analog pin: 0?5 on ATMega328p
  ADMUX = ADMUX | channel;
  //New Conversion
  ADCSRA |= (1 << ADSC);
  //Do a preliminary conversion
  ADCSRA |= (1 << ADSC);
  //Wait until conversion is finished
  while (ADCSRA & (1 << ADSC));
  //Return ADC value

  return (float)ADCW;
}

int main() {

	// initialize the four-seven segment display pin as an output
	DDRD = 0b11111100;//f,e,d,c,b,a
	DDRB = 0b111111;//d1,d2,d3,d4,h,g

	float adcReadValue;
	InitADC();

	while (1) {
		
		adcReadValue = ADC_Read(inPin);

		temperature = adcReadValue * (5.0 / 1024.0) * 100 * 100;
		int temp = (int)temperature;

		clearLEDs();//clear the 7-segment display screen
		pickDigit(0);//Light up 7-segment display d1
		pickNumber((temp / 1000)); // get the value of thousand
		_delay_ms(100);//delay 5ms

		clearLEDs();//clear the 7-segment display screen
		pickDigit(1);//Light up 7-segment display d2
		pickNumber((temp % 1000) / 100); // get the value of hundred
		_delay_ms(100);//delay 5ms

		clearLEDs();//clear the 7-segment display screen
		pickDigit(2);//Light up 7-segment display d3
		pickNumber(temp % 100 / 10); //get the value of ten
		_delay_ms(100);//delay 5ms

		clearLEDs();//clear the 7-segment display screen
		pickDigit(3);//Light up 7-segment display d4
		pickNumber(10); //Get the value of single digit
		_delay_ms(100);//delay 5ms		
	}
	return 0;
}
