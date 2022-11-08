#include <xc.h>
#include "Functions.h"
#include <math.h>
#include "ADC.h"
#include "LEDarray.h"
#include "interrupts.h"
#include "Global Variables.h"
/************************************

************************************/
int month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
void streetLightInit(void){
    
    LATHbits.LATH3 = 0; //set initial output state
    TRISHbits.TRISH3 = 0; //set TRIS value for pin (output)
    LATDbits.LATD7 = 1; //set initial output state
    TRISDbits.TRISD7 = 0; //set TRIS value for pin (output)
}
void increment()
{
    if (year%4 == 0)
    {
        month[1] = 29;
    }
    else 
    {
        month[1] = 28;
    }
    if (seconds == 1)
    {
        hour++;
        LEDarray_disp_bin(hour);
        seconds = 0; 
    }
    if (hour == 24)
    {
        day_of_year++;
        day_of_week++;
        day_of_month++;
        hour = 0;
    }
    if (day_of_week == 7)
    {
        day_of_week = 0;
    }
    if (day_of_month == month[month_num-1])
    {
        day_of_month = 0;
        month_num++;
    }
    if (month_num == 13)
    {
        month_num=0;
        year++;
    }
}

void poweroff()
{
        //int a = ADC_getval();
        if (1 <= hour && hour < 5) {
            LATHbits.LATH3 = 0;

}
}

void day1_init()
{ //Start code on 1st Jan 2022 at 00:00 (12am)
    seconds = 0;
    hour = 0;
    day_of_year = 1;
    day_of_month = 1;
    day_of_week = 6; //1 (Monday) to 7(Sunday), 6 is Saturday
    year = 2022;
    month_num = 1;
    LATHbits.LATH3 = 1;
}

int sunrise()
{
    int prevState = LATHbits.LATH3;
    int sunrise_time = 0;
    if (5<=hour<=8)
    {
        if (prevState==1 && LATHbits.LATH3==0)
        {
            sunrise_time = seconds+(hour*3600);
        }
    }
    return sunrise_time;
}

int sunset()
{
    int prevState = LATHbits.LATH3;
    int sunset_time = 0;
    if (16<=hour<=20)
    {
        if (prevState==0 && LATHbits.LATH3==1)
        {
            sunset_time = seconds+(hour*3600);
        }
    }
    return sunset_time;
}

void timeadjuster(int sunrise_time, int sunset_time)
{
    int solarnoon = 0;
    int adjustment = 0;
    solarnoon = (sunrise_time+sunset_time)/2;
    adjustment = (12*3600)-solarnoon;
    if (hour==11 && seconds==1800)
    {
        seconds+=adjustment;
    }
}
void daylightsavings()
{
    if (month_num ==3 && day_of_week==7 && 25<=day_of_month<=31)
    {
        hour++;
    }
    if (month_num ==10 && day_of_week==7 && 25<=day_of_month<=31)
    {
        hour--;
    }
    
}