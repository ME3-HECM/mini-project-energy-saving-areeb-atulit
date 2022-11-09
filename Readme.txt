Read Me file for project which will go through our code:

Syntax information: 
We are going to be using human notation for days and months. This means that our week 
goes from 1 to 7, rather than 0 to 6, with 1 being Monday and 7 being Sunday. 

Furthermore days of the month start at 1 and get reset to 1 in each month, not 0, 
to be consistent with our human notation. 

Start Date for code: 
The code starts off by initializing day 1 (start date) in day1_init()
We are starting our code on 1st January 2022 at 12:00am (00:00), which is a Saturday (day 6).
The purpose of starting off our code on 1/1/22 is to make it easier for the setup to initialise. 

Toggling LED during sunrise and sunset: 

First of all, the toggling of the LED is triggered using interrupts, with the toggle being 
placed in the high priority interrupt (more explanation in the interrupts section). 

The toggling is due to the comparator sensing a rising or falling edge via comp_rise() and comp_fall()
We do not use the readings from the LDR (ADC_getval()) as it was unessassary, the comparator does its job properly. 

The code is hard wired to turn the LED on at 00:00am, as it is when we start the entire case off
(and to ensure the comparator falling and rising toggle does not get reversed). 
The code then force switches the LED off between the hours 01:00 and 05:00, as per the requirements. From there, at 05:00, 
the LED switches back on, and from there the toggling of the LED is left to the comparator interrupt. 
 
At sunrise, the LED will toggle off and at sunset, it will toggle back on. 

Interrupts: 

Both high and low priority interrupts are being used in this project. 

    Low Priority Interrupt: 
    
    In the low priority interrupt, we will have the timer interrupt, which will increment our seconds 
    variable every second. From Lab 3, we coded the timer to overflow within 1 second, using a prescaler value
    of 256 and initial starting number of 3035 (split into TMROH and TMROL). 
    
    The second if statement in the low priority interrupt is the turning back of the LED at 05:00. (Do we need it in interrupt)

    High Priority Interrupt: 
    
    In the high priority interrupt, we have the toggling of the LED due to the comparator interrupt. 
    Once the comparator detects a falling edge or rising edge, it will trigger the comparator flag, 
    which will toggle the LED. 

Variables: 

    The variables used in the project are defined in the global variables header file: 
    seconds, hours, days (of week, month and year), year
    
    The tracking of which month it is, is done via an array and the variable month_num, which will keep 
    track of the month index we are in, once the days of month variable crosses the corresponding month days. 

Incrementation of variables: 
    The incrementation of the variables is done in the increment() function

Daylight Savings: 
    Daylight savings is adjusted for in the daylightsavings() function.
    Daylight savings occurs on the last sunday of march and october, and is always between days 25 and 31. 
    So our code has an if statement which checks if the month is either March (3) or October (10), if the day
    is Sunday (7) and is between days 25 and 31 and if the hour is 1am (for march) or 2am (for oct)
    If it is, then the hour timer is changed accordingly. 

Time Adjustment: 
    As the microcontroller will end up having errors in the time increments, an adjustment has to be made.  
    Our adjustment happens everyday, at 23:30 (11:30pm). 

    The logic behind the adjustment is as follows: 
    The sunrise time is recorded in seconds, via the sunrise_time() function, 
    which has an if statement to check between 5am to 8am and see if the LED has been toggled (using previous state and current state of LED pin)
    
    The same is done for the sunset time, and noon is calculated by taking the average of sunrise and sunset time.
    The actual noon is assumed to be at 12:00 (12pm) exactly, so any deviation, from that is our error. 
    The error is stored in the variable adjustment, which gets added to the seconds at 11:30pm. The assumption there is that the error is not bigger than 30mins. 

