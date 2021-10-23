/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "timer.h"
#include <avr/interrupt.h>
#include "simAVRHeader.h"
#endif

enum States { Start, init, incr, decr, reset } State;
unsigned char i = 0x00; //counter

void Tick() {
	
    switch(State) {
        case Start:
            PORTB = 0x07;
            State = init;
            break;

        case init: 
            if(PINA == 0xFD) {
                State = decr;
		
            }
            if(PINA == 0xFC){
                State = reset; 
            }
            if(PINA == 0xFE) {    
                State = incr; 
            }
            if(PINA == 0xFF) {
                State = init; 
            }     
            break;

        case incr: 
            if(PINA == 0xFC) {
                State = reset;
                PORTB = 0x0;
            }
            if(PINA == 0xFD) {
                State = decr;
            }
            if(PINA == 0xFE) {
                i++; State = incr;
                
		if(i == 10){
		        i = 0;
		        State = incr;
            	}
            }
            
            if(PINA == 0xFF){
                State = init; 
            }
		
            break;

        case decr: 
            if(PINA == 0xFC) {
                State = reset;
                PORTB = 0x0;
            }
            if(PINA == 0xFE) {
                State = incr; i++;
            }
            if(PINA == 0xFF){
                State = init;
            }
            if(PINA == 0xFD) {
                State = decr;
                i++;
		if(i == 10) {
		        State = decr;
		        i = 0;
            	}    
            }
              
            break;

        case reset: 
            if(PINA == 0xFE) {  
                State = incr;
            }
            if(PINA == 0xFD) {
                State = decr;
            }
            if(PINA == 0xFF){
                State = init;
            }   
            break;

        default: 
            State = Start;
            break; 
    }

	switch(State) {
	case Start: 
            PORTB = 0x07;
            break;

        case init: 
            i = 0;
            break;

        case incr: 
            if(PORTB < 9) {
                PORTB = PORTB + 1;
            }
            break;

        case decr: 
            if(PORTB > 0) {
                PORTB = PORTB - 1;
            }
            break;

        case reset: 
            PORTB = 0x0;
            break;

        default: 
            PORTB = 0x07;
            break;

}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

	TimerSet(100);
	TimerOn();

    /* Insert your solution below */
    while (1) {
        Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}
