/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Turn on and off a LED
*/

int main(){
    
    DDRD |= | (1 << PD2); // Set pin 2 (PD2) as an output pin
        
    while(1){
        
        PORTD |= (1 << PD2); // Set pin 2 (PD2) to 1, (turn on the bulb)
        _delay_ms(1000); // delay for one second
        PORTD &= ~(1 << PD2); // Set pin 2 (PD2) to 0, (turn off the bulb)
        _delay_ms(1000); // delay for one second
    }
    
    return 0;
}