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
    streetLightInit();                  
    LEDarray_init();                     
    Timer0_init();                       
    Comp1_init_rising_edge();            //initialise comparator to detect rising edge (LDR reads dark to light)
    Comp1_init_falling_edge();           //initialise comparator to detect falling edge (LDR reads light to dark)
    Interrupts_init();                   
    ADC_init();                          
    day1_init();
    LCD_Init();
    char strtime[100];
    char strdate[100];
    test_day(); //shorten duration of hours and days for test mode
    //real_day();//set duration of hours and days to reflect real world
    while (1) {
        LCD_setline(1); //Set Line 1
        time2String(strdate,hour,seconds,day_of_month, month_num,year);
        increment();                    //update counters of all units of time
        poweroff();                     //check if time is between 1 and 5 AM and power light off if so
        //sunrise();                      //check for sunrise and record time of event when it occurs
        //sunset();                       //check for sunrise and record time of event when it occurs
        time_adjuster(sunrise(),sunset());//Daily time adjustment to remain synchronous with sun
        daylightsavings();               

        }
    }


