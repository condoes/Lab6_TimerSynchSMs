/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum states {start, init, light_change, B_press, B_release} state;
unsigned char tmpA = 0x00;
unsigned char arr[3] = {0x01, 0x02, 0x04};
unsigned char i = 0;
//unsigned char tmpB = 0x00;

void Tick() {
	switch(state) {
        case start:
            state = init;
            PORTB = arr[0];
		i = 1;
            break;

        case init:   
	tmpA = ~PINA & 0x01;
            if(tmpA == 0) {
		if(i < 3) {
                    PORTB = arr[i];
                    i++;
                }
		if(i == 3) { i--; state = light_change; }
              

            }
            else{
                state = B_press;
		
            }
            break;

        case light_change: 
	tmpA = ~PINA & 0x01;    
            if(tmpA == 0) {
		if(i != 0) { i--; PORTB = arr[i]; }
		if(i == 0) {i++; state = init;}
                }
            else {
                state = B_press;
            }
            break;

        case B_press: 
	if(~PINA & 0x01 == 1){
            state = B_press;	  
            }
	else{
	state = B_release;
	}	

            break;

        case B_release:               
            if(~PINA & 0x01){
                i = 0;
		//PORTB = arr[0];
                state = init;
            }
	else {
                state = B_release;
		
	}
break;
          
        default: 
            state = start;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	//unsigned char tmpB = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
        while(!TimerFlag) {};
        TimerFlag = 0;
    }
return 1;
}
