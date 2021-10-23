/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: 

DEMO LINK: https://drive.google.com/file/d/1QcPh6grZiNpIF_nnbxLxdDL3cpMfZkEB/view?usp=sharing
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

enum States { Start, init, incr, decr, reset } State;
unsigned char i = 0x00; //counter for 1000ms
unsigned char tmpA = 0x00;

void Tick() {
	
    switch(State) {
        case Start:
            PORTB = 0x07;
            State = init;
            break;

        case init: 
            tmpA = ~PINA & 0x03;
            if(tmpA == 0x02) {
                State = decr;
                if (PORTB > 0) {
                    PORTB = PORTB - 1;
                }
                i = 0;
            }
            if(tmpA == 0x03){
                State = reset;
                PORTB = 0x00;
            }
            if(tmpA == 0x01) {
                State = incr;
                if (PORTB < 9) {
                    PORTB = PORTB + 1;
                }
                i = 0;
            }
            if(tmpA == 0) {
                State = init;
            }
            break;

        case incr: 
            tmpA = ~PINA & 0x03;
            if(i == 10) {
                if(PORTB < 9) {
                    PORTB = PORTB +1;
                }
                i = 0;
            }
            if(tmpA == 3) {
                State = reset;
                PORTB = 0x00;
            }
            
            if(tmpA == 1) {
		State = incr;
		i++;
            }
            else if(tmpA == 0){
                State = init;
            }
		
            break;

        case decr: 
            tmpA = ~PINA & 0x03;
            if(i == 10) {
                if(PORTB > 0) {
                    PORTB = PORTB - 1;
                } 
		        i = 0;
            }
            if(tmpA == 3) {
                State = reset;
                PORTB = 0x00;
            }
            
            if(tmpA == 2) {
                State = decr;
		i++;
            }
            else if(tmpA == 0){
                State = init;
            }  
            break;

        case reset: 
            tmpA = ~PINA & 0x03;
            if(tmpA == 1) {  
                State = incr;
		        if(PORTB < 9) { PORTB = PORTB + 1; }
		        i = 0;
            }
            if(tmpA == 2) {
                State = decr;
            }
            if(tmpA == 0){
                State = init;
            }   
            break;

        default: 
            State = Start;
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
	State = Start;

    /* Insert your solution below */
    while (1) {
        Tick();
        while(!TimerFlag) {};
        TimerFlag = 0;
    }
    return 1;
}
