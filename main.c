// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "Functions.h"
#include "Global Variables.h"
#include "ADC.h"
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {

    LATHbits.LATH3 = 1; //set initial output state
    TRISHbits.TRISH3 = 0; //set TRIS value for pin (output)
    LATDbits.LATD7 = 1; //set initial output state
    TRISDbits.TRISD7 = 0; //set TRIS value for pin (output)
    //call your initialisation functions to set up the hardware modules
    hour = 1;
    DAC_init();
    LEDarray_init();
    Timer0_init();
    Comp1_init();
    Comp1_inithigh();
    Interrupts_init();
    ADC_init();
    int a = ADC_getval();
    //int hour = 0;
    while (1) {
        increment();
        a = ADC_getval();
        if (1 < hour && hour < 5) {
            LATHbits.LATH3 = 0;
        } else if (a < 50 && (hour > 5 || hour < 1)) {
            LATHbits.LATH3 = 1;

        }
//        __delay_ms(50);
    }
}


