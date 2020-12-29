/* 
 * File:   IOs.c
 * Author: ruhajaved
 *
 * Created on October 11, 2020, 1:02 PM
 */

#include <xc.h>          // include header file xc.h
#include "IOs.h"        // include header file IOs.h
//#include "TimeDelay.h"

static uint8_t flag = 0; // declare variable flag to help start/pause/turn off timer
static uint16_t min = 0,sec = 0; // declare min and sec globals to keep track of countdown value

void IOinit() 
{
   TRISBbits.TRISB8 = 0; // make GPIO RB8 a digital output
   
   AD1PCFG = 0xFFFF; // Turn all analog pins as digital  
   TRISAbits.TRISA2 = 1; // make GPIO RA2 a digital input
   CNPU2bits.CN30PUE = 1; // enable pull up resistor on RA2/CN30
   
   TRISAbits.TRISA4 = 1; // make GPIO RA4 a digital input
   CNPU1bits.CN0PUE = 1; // enable pull up resistor on RA4/CN0
   
   TRISBbits.TRISB4 = 1; // make GPIO RB4 a digital input
   CNPU1bits.CN1PUE = 1; // enable pull up resistor on RB4/CN1
   
   return;
}

void IOcheck()
{
    uint16_t cntr = 0; // use to track how long PB3/RB4 is pressed
    
    while(PORTAbits.RA2 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1 && min <= 59) // while RA2, pb1 is pressed
    {
        min++;          // increment minute count
        print_m_s();    // print current timer value
        XmitUART2(' ', 9); // print space characters in order to clear any previous ALARM messages
        delay_ms(500);  // 500 ms delay to set pace of increment (don't want it to be super fast)
    }
    while(PORTAbits.RA2 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0 && sec <= 59) // while RA4, pb2 is pressed
    {
        sec++;          // increment second count
        print_m_s();    // print current timer value
        XmitUART2(' ', 9); // print space characters in order to clear any previous ALARM messages
        delay_ms(500);  // 500 ms delay to set pace of increment
    }
    while(PORTAbits.RA2 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) // while RB4, pb3 is pressed
    {
        cntr++;         // increment counter by 1
        delay_ms(100);  // delay of 100 ms  
    }
    
    if (cntr < 30 && cntr != 0) // if PB3 is pressed for < 3 seconds (3000/100 = 30)
        flag = !flag;           // either start the countdown or pause the countdown
    else if (cntr != 0)         // if PB3 is pressed for > 3 seconds
    {
        flag = 0;               // clear flag, meaning effectively stop the timer
        min = 0;                // zero minute count
        sec = 0;                // zero second count
        LATBbits.LATB8 = 0;     // turn off LED
        print_m_s();            // print cleared timer 
        XmitUART2(' ', 9);      // print space characters in order to clear any previous ALARM messages    
    }
    
    while (flag == 1 && PORTBbits.RB4 != 0 && (min != 0 || sec != 0)) /* while countdown is active, 
                                                                       * PB3 isn't pressed and
                                                                       * min & sec don't both equal to zero */
    {
        LATBbits.LATB8 = !LATBbits.LATB8;   // turn on or off the LED
        print_m_s();                        // print current timer value
        decrement();                        // decrement timer by 1 s
        delay_ms(405);                     /* wait for 1 s, but given the lag due to a 32kHz clk, 
                                            * delay is actually set to 405 ms */
    }
    
     if (flag == 1 && min == 0 && sec == 0) // if timer is active and countdown has reached 00 m : 00 s
    {
        print_m_s();                       // print current timer value
        Disp2String(" -- ALARM");          // print --ALARM on terminal 
        LATBbits.LATB8 = 1;                // turn on LED until the timer is reset
        flag = 0;                          // set flag to 0 to shutoff the timer
    }
    
    return;
}
    
void decrement()
{
    int total = min*60 + sec;   // convert current time in min and sec into seconds only
    total--;                    // decrement time by 1 s
    min = total/60;             // convert back to min and sec
    sec = total%60;             // convert back to min and sec
}

void print_m_s()
{
   char str[12];                                /* declare array to host string used to 
                                                 * display timer value on terminal */
   sprintf(str, "\r%02dm : %02ds", min, sec);   // fill str with appropriate characters to display
   Disp2String(str);                            // display str on the terminal
}
