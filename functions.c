#include <xc.h>
#include "Functions.h"
#include <math.h>
#include "ADC.h"
#include "LEDarray.h"
#include "interrupts.h"
#include "Global Variables.h"
/************************************

 ************************************/
//define array with number of days in each month of the year
int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int adjustment_of_day = 1;

// function to initialise street light LED

void streetLightInit(void) {
    LATHbits.LATH3 = 0; //set initial output state
    TRISHbits.TRISH3 = 0; //set TRIS value for pin (output)
}

//shorten duration of hours and days for test mode

void test_day() {
    seconds_in_hour = 10; //define number of seconds in hour
    hours_in_day = 24;   //define number of hours in day
}

//set duration of hours and days to reflect real world

void real_day() {
    seconds_in_hour = 3600; //define number of seconds in hour
    hours_in_day = 24; //define number of hours in day
}
//Function to update and reset counters for each division of time (second, hour, day, month, year)

void increment() {

    if (year % 4 == 0) month[1] = 29; //February has 29 days in leap years
    if (year % 4 != 0) month[1] = 28; //February has 28 days if not a leap year

    //increment hour and reset seconds at the end of each hour
    if (seconds == seconds_in_hour) {
        hour++; //Increment hour counter
        LEDarray_disp_bin(hour); //Display hours on LED strip
        seconds = 0; //reset seconds counter
    }

    //increment day and reset hour at the end of the day
    if (hour == hours_in_day) {
        day_of_year++; //increment day of year
        day_of_week++; //increment day of week
        day_of_month++; //increment day of month
        hour = 0; //reset hour counter to zero
        adjustment_of_day = 1;
    }

    //reset day at the end of the week
    if (day_of_week == 8) //changed from 7 to 8
        day_of_week = 1; //reset day of week back to 1 

    // update month counter on last day of the month
    if (day_of_month == month[month_num - 1] + 1) {
        day_of_month = 1; //Reset days of the month counter to 1
        month_num++; //increment month counter
    }
    if (month_num == 13) {
        month_num = 1; //reset month back to January
        year++; //increment year
    }
}

// Function to switch streetlight off between 1AM and 5AM every day

void poweroff() {
    if (1 <= hour && hour < 5) LATHbits.LATH3 = 0; //LED always off when time is in between 1 and 5 AM
}

void day1_init() { //Start code on 1st Jan 2022 at 00:00 (12am)
    seconds = 0;
    hour = 23;
    day_of_year = 1;
    day_of_month = 1;
    day_of_week = 1; //1 (Monday) to 7(Sunday), 6 is Saturday
    year = 2022;
    month_num = 1;
    LATHbits.LATH3 = 1;
}

//function to record sunrise time

/*int sunrise() {
    int prevState = 1; //store previous state of LED
    //if (LATHbits.LATH3 == 1 && hour > 5)
     //   prevState = 1;
    
    int sunrise_time = 0; //Initialise sunrise time
    //check for sunrise only between 5AM and 8AM 
    if (5 <= hour <= 8) {
        if (prevState == 1 && LATHbits.LATH3 == 0) //check that street light has gone from high to low state
            sunrise_time = seconds + (hour * 3600); //calculate sunrise time in seconds
    }
    SR=sunrise_time;
    prevState = 0;
    //return sunrise_time;
    return prevState;
}
 

//function to record sunset time

int sunset() {
    int prevState = LATHbits.LATH3; //store previous state of LED
    int sunset_time = 0; //Initialise sunrise time
    //check for sunset only between 4PM and 8PM 
    if (16 <= hour <= 20) {
        if (prevState == 0 && LATHbits.LATH3 == 1) //check that street light has gone from low to high state
            sunset_time = seconds + (hour * 3600); //calculate sunset time in seconds
    }
    return sunset_time;
}
 */

//Adjust the time at the end of the day to be synchronous with the sun

void time_adjuster(int sunrise_time, int sunset_time) {
    
    int solarnoon = 0;                              //initialise variable to store solar noon                              
    int adjustment = -2;                            //initialise variable to store required daily time adjustment
    solarnoon = (sunrise_time + sunset_time) / 2;   //Calculate average of sunrise and sunset time which is solar noon
    //adjustment = (12 * 10) - solarnoon;           //Difference between solar noon and noon as per PIC timer
    if (hour == 23 && seconds == 5  && adjustment_of_day == 1)
    {   
        seconds += adjustment;                      //adjust time at 23:30 every day
        adjustment_of_day = 0;
    }
    SN = solarnoon;
    AD = adjustment;
    
}

//Perform daylight savings time adjustment on the last Sunday of March and October

void daylightsavings() {
    if (month_num == 3 && day_of_week == 7 && 25 <= day_of_month <= 31 && hour == 1)
        hour++; //Turn the clock forward by 1 hour on the last Sunday of March

    if (month_num == 10 && day_of_week == 7 && 25 <= day_of_month <= 31 && hour == 2)
        hour--; //Turn the clock back by 1 hour on the last Sunday of October
}