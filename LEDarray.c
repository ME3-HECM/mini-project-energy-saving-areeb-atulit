#include <xc.h>
#include "LEDarray.h"
#include <math.h>
#include "ADC.h"
#include "Global Variables.h"
/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    	//set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
	//set initial output LAT values (they may have random values when powered on)
    
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
}
/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
	//see Readme.md for examples
    int mask= 0b000000001;//initialise mask
    int led_arr[9];//array corresponding to 9 LED pins
    for(int ctr=0;ctr<9;ctr++){
        if (number & mask)//if bit turned on by mask is 1, turn on corresponding LED
            led_arr[ctr]=1;
                
        else
            led_arr[ctr]=0;
        
        mask<<=1;//left shift mask to check next bit in next loop iteration
    }
    //copy LED array with state of each LED into respective pins. 
    LATGbits.LATG0 = led_arr[0];
    LATGbits.LATG1 = led_arr[1];
    LATAbits.LATA2 = led_arr[2];
    LATFbits.LATF6 = led_arr[3];
    LATAbits.LATA4 = led_arr[4];
    LATAbits.LATA5 = led_arr[5];
    LATFbits.LATF0 = led_arr[6];
    LATBbits.LATB0 = led_arr[7];
    LATBbits.LATB1 = led_arr[8];
}
/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{ //some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
     unsigned int shift = number/10;
     unsigned int bitmask = 0b000000001;
     unsigned int disp_val = (bitmask << shift) -1;
     LEDarray_disp_bin(disp_val);
}
/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	 unsigned int disp_val;
     unsigned int shift = cur_val/10;
     unsigned int bitmask = 0b000000001;
    
     unsigned int shiftmax = max/10;
     unsigned int bitmaskmax = 0b000000001;
     cur_val = (bitmask << shift) -1;
     max = (bitmaskmax << shiftmax);
     disp_val = cur_val | max;
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator

	LEDarray_disp_bin(disp_val);	//display value on LED array
}

int incrementseconds(int seconds)
{
    seconds++;
    LEDarray_disp_bin(seconds);
    return seconds;
}