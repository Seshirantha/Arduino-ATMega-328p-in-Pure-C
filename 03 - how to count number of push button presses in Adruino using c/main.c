/*
* Author : Shirantha Madusanka (Software Engineering, University of Kelaniya, Sri Lanka)
* Date : 28/07/2019
* Divice : Arduino Uno - ATmega328p
* Purpose : Count number of push button presses using C
*/

int val;                        // Variable for reading the pin status
int buttonState;                // Variable to hold the button state
int buttonPresses = 0;          // Variable to hold number of button presses

int main(){

    DDRD &=  0b11111011; // Set pin PD2 as output
    buttonState = PIND & 0b00000100; // Read initial state
    
    while(1){
        val = PIND & 0b11111011; 
        if (val != buttonState){
            if (val == 0){
                buttonPresses++;
            }
        }
        buttonState = val; 
    }
    
    return 0;
}
