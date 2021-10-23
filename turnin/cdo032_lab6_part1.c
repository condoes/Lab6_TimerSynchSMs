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

enum states {start, B0, B1, B2} state;

void Tick() {
	switch(state) {
        case start:
            state = B0;
            break;

        case B0: 
            state = B1;
            PORTB = 0x01;
            break;
        
        case B1: 
            state = B2;
            PORTB = 0x02;
            break;

        case B2: 
            state = B0;
            PORTB = 0x04;
            break;

        default: 
            state = start;
            PORTB = 0x01;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
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
