#include <xc.h>
#include "Functions.h"
#include <math.h>
#include "ADC.h"
#include "LEDarray.h"
#include "interrupts.h"
#include "Global Variables.h"
/************************************

************************************/
void increment()
{
    
    if (seconds == 1)
    {
        hour++;
        LEDarray_disp_bin(hour);
        seconds = 0;
        
    }
    
    if (hour == 24)
    {
        day++;
        hour = 0;
    }
    
    if (day%7 == 0)
    {
        week++;
    }
    if (day == 365)
    {
        year++;
    }
    
}

void poweroff()
{
        //int a = ADC_getval();
        if (1 < hour && hour < 5) {
            LATHbits.LATH3 = 0;

}
}