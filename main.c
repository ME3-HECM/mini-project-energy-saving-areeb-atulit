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
    Interrupts_init();                   //initialise interrupts                        
    day1_init();                         //initialise day 1
    LCD_Init();
    char strdate[100];                   //String for LCD display
    test_day();                          //shorten duration of hours and days for test mode
    //real_day();                        //set duration of hours and days to reflect real world
    while (1) {
        increment();                    //update counters of all units of time
        LEDarray_disp_bin(hour);        //Display hours on LED strip
        poweroff();                     //check if time is between 1 and 5 AM and power light off if so    //check for sunrise and record time of event when it occurs
        time_adjuster(SR,SS);           //Daily time adjustment to remain synchronous with sun
        daylightsavings(); 
        
        //LCD Display
        LCD_setline(1);
        time2String(strdate,seconds,hour,day_of_month,month_num,year); //Display time and date
        //timeadj2String(strdate,SS,SR,adjustment_of_day,AD,seconds); //display time adjustment 
        }
    }


