/*
 * File:   main.c
 * Author: Rushi V
 *
 * Created on September 26, 2020, 9:17 PM
 */

// MPLAB header libraries
#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "IOs.h"
#include "ChangeClk.h"
#include "TimeDelay.h"
#include "UART2.h"

#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled

// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}      //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}       //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");}

void main(void) {
     
     NewClk(32); // set clock to 32 kHz
     IOinit();   // call IOinit to initialize the IO ports
     InitUART2(); // call InitUART2 to initialize the UART
    
    while(1)
    {
        IOcheck(); // call IOcheck to implement IO checks and LED blinking functions
    }
    
    return;
}
