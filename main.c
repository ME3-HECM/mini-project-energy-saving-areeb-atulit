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
#include "LCD.h"
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    //call your initialisation functions to set up the hardware modules
    streetLightInit(); //initialise street light
    LEDarray_init();//initialise LED strip
    Timer0_init();//initialise timer
    Comp1_init_rising_edge();//initialise comparator
    Comp1_init_falling_edge();
    Interrupts_init();
    ADC_init();
    day1_init();
    LCD_Init();
    char strtime[100];
    char strdate[100];
    while (1) {
        increment();
        poweroff();
        sunrise();
        sunset();
        timeadjuster(sunrise(),sunset());
        daylightsavings();
//        LCD_setline(1); //Set Line 2
//        time2String(strtime,hour,seconds);
        LCD_setline(2); //Set Line 2
        date2String(strdate, day_of_year, month_num,year);
        }
    }


