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
    hour = 0;
    //call your initialisation functions to set up the hardware modules
    streetLightInit(); //initialise street light
    LEDarray_init();//initialise LED strip
    Timer0_init();//initialise timer
    Comp1_init_rising_edge();//initialise comparator
    Comp1_init_falling_edge();
    Interrupts_init();
    ADC_init();
    while (1) {
        increment();
        poweroff();
        }
    }


