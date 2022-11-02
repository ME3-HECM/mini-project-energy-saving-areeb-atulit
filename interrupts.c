#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE=1; 	//enable interrupt source INT0
    PIE0bits.TMR0IE=1;  //Enable timer interrupt
    INTCONbits.IPEN=1;  //Enable Priority in interrupts
    INTCONbits.PEIE=1;  //Enable Peripherial interrupts
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
    
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{

}

void __interrupt(low_priority) LowISR()
{
    if(PIR2bits.C1IF){ 					//check the interrupt source
        LATHbits.LATH3 = !LATHbits.LATH3; //toggle LED
        PIR2bits.C1IF=0; 						//clear the interrupt flag!				//clear the interrupt flag! 
    }
    if(PIR0bits.TMR0IF){ 					//check the interrupt source for the timer interrupt
        LATHbits.LATH3 = !LATHbits.LATH3;       //toggle LED
        PIR0bits.TMR0IF = 0;                    //clear the interrupt flag!
}
}

