#include <msp430.h> 
/*
 *  flash green and toggle red when key is pressed
 */
    void REDblink();
    void GREENblink();

#define LED_RED          BIT0  // F5529 RED is P1.0, GREEN is P4.7
#define LED_GREEN     BIT7
#define KEY            BIT1  // F5529 S1 is P2.1, S2 is P1.1

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
P1DIR = LED_RED; // Set P1.0 to output direction
P1OUT = ~ LED_RED; // Set the LED off and KEY not pressed
P1REN |= KEY;    // enable internal pullup resistor for the button
P4DIR = LED_GREEN;
P4OUT = ~ LED_GREEN;
P4REN |= KEY;

 while (1) {
     if ( (P1IN & KEY) ==0 ) {
         DelayMS(1000);
         if ((P1IN & KEY) == 0 ) GREENblink();
         else REDblink();
         }
     }
}

void REDblink(){
    P1DIR |= 0x01;    // Set P1.0 - RED LED to output direction
    P1OUT |= 0x01;    // turn ON RED LED by bitwise OR
    DelayMS(100);
    P1OUT &= 0xFE;    // turn OFF RED LED by bitwise AND
}

// green blink with "length" millisecond
void GREENblink(int length){
    P4DIR |= 0x80;    // Set P1.6 - GREEN LED to output direction
    P4OUT |= 0x80;    // turn ON GREEN LED by bitwise OR
    DelayMS(length);
    P4OUT &= 0x7F;    // turn OFF LED by bitwise AND
}

void DelayMS(unsigned int ms) {
    volatile unsigned int d;
    for (d= ms*100; d>0; d--);
}
