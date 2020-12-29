/* 
 * File:   TimeDelay.c
 * Author: ruhajaved
 *
 * Created on October 21, 2020, 7:12 PM
 */

// include MPLAB header files
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>

// include user-defined header file TimeDelay.h
#include "TimeDelay.h"

void delay_ms(uint16_t time_ms)
{
    //Configure TMR2
    T2CONbits.TON = 0;      // disable TMR2
    T2CONbits.TSIDL = 0;    // continue module operation in idle mode
    T2CONbits.T32 = 0;      // use TMR2 as a 16-bit timer
    T2CONbits.TCS = 0;      // use internal clock
    TMR2 = 0;               // clear TMR2
    
    PR2 = time_ms * (32000 / 2000); // calculate PR2 based on desired delay time_ms
    
    // configure TMR2 interrupt
    IPC1bits.T2IP = 0x07;   // set interrupt priority to 7, the highest
    IFS0bits.T2IF = 0;      // clear TMR2 flag bit
    IEC0bits.T2IE = 1;      // enable TMR2 interrupt
    
    T2CONbits.TON = 1;      //start TMR2 
    
    Idle();                 // put MCU in idle mode until TMR2 interrupt occurs
    
    return;
}

void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void)
{
    IFS0bits.T2IF = 0;      // clear TMR2 flag bit
    T2CONbits.TON = 0;      // disable TMR2 
    
    return;
}

