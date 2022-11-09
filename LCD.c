#include <xc.h>
#include "LCD.h"
#include <stdio.h>
/************************************
 * Function to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
 ************************************/
void LCD_E_TOG(void) {
    LATCbits.LATC2=1;//turn the LCD enable bit on
    __delay_us(2); //wait a short delay
    LATCbits.LATC2=0;//turn the LCD enable bit off again
}

/************************************
 * Function to set the 4-bit data line levels for the LCD
 ************************************/
void LCD_sendnibble(unsigned char number) {

    //set the data lines here (think back to LED array output)
    if(number&0b0001) LATBbits.LATB3=1;
    else LATBbits.LATB3=0;
    if(number&0b0010) LATBbits.LATB2=1;
    else LATBbits.LATB2=0;
    if(number&0b0100) LATEbits.LATE3=1;
    else LATEbits.LATE3=0;
    if(number&0b1000) LATEbits.LATE1=1;
    else LATEbits.LATE1=0;
    LCD_E_TOG(); //toggle the enable bit to instruct the LCD to read the data lines
    __delay_us(5); //Delay 5uS
}

/************************************
 * Function to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
 ************************************/
void LCD_sendbyte(unsigned char Byte, char type) {
    if(type&0b1)
    {
        LATCbits.LATC6 = 1; 
    }
    else 
    {
        (LATCbits.LATC6 = 0);// set RS pin whether it is a Command (0) or Data/Char (1) using type argument
    }
    LCD_sendnibble(Byte>>4);// send high bits of Byte using LCDout function
    LCD_sendnibble(Byte);// send low bits of Byte using LCDout function
    __delay_us(50); //delay 50uS (minimum for command to execute)
}

/************************************
 * Function to initialise the LCD after power on
 ************************************/
void LCD_Init(void) {

    //Define LCD Pins as Outputs and
    //set all pins low (might be random values on start up, fixes lots of issues)
    TRISCbits.TRISC2 = 0;//ENABLE
    TRISCbits.TRISC6 = 0;//RS
    
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE3 = 0;

    LATBbits.LATB3 = 0;
    LATBbits.LATB2 = 0;
    LATEbits.LATE1 = 0;
    LATEbits.LATE3 = 0;
    
    LATCbits.LATC2 = 0;//ENABLE
    LATCbits.LATC6 = 0;//RS
    __delay_ms(40);
    //Initialisation sequence code
    // follow the sequence in the GitHub Readme picture for 4-bit interface.
    // first Function set should be sent with LCD_sendnibble (the LCD is in 8 bit mode at start up)
    // after this use LCD_sendbyte to operate in 4 bit mode
    LCD_sendnibble(0b0011);
    __delay_us(40);
    LCD_sendbyte(0b00101100,0);
    __delay_us(40);
    LCD_sendbyte(0b00101100,0);
    __delay_us(40);
    LCD_sendbyte(0b00001100,0);
    __delay_us(40);
    LCD_sendbyte(0b00000001,0);
    __delay_ms(1.53);
    LCD_sendbyte(0b00000111,0);
    LCD_sendbyte(0b00001100,0);
    //remember to turn the LCD display back on at the end of the initialisation (not in the data sheet)
}

/************************************
 * Function to set the cursor to beginning of line 1 or 2
 ************************************/
void LCD_setline(char line) {
    if(line&0b01) 
    {
        LCD_sendbyte(0x80,0);//Send 0x80 to set line to 1 (0x00 ddram address)
    }
    if(line&0b10) 
    {
        LCD_sendbyte(0xC0,0);//Send 0xC0 to set line to 2 (0x40 ddram address)
    }
}

/************************************
 * Function to send string to LCD screen
 ************************************/
void LCD_sendstring(char *string) {
    //code here to send a string to LCD using pointers and LCD_sendbyte function
{	  
	while(*string != 0){  // While the data pointed to isn?t a 0x00 do below (strings in C must end with a NULL byte) 
		LCD_sendbyte(*string++,1); 	//Send out the current byte pointed to and increment the pointer
	}
}
}

/************************************
 * Function to send string to LCD screen
 ************************************/
void LCD_scroll(void) {
    //code here to scroll the text on the LCD screen
    LCD_sendbyte(0b00011000,0);
    __delay_ms(50);
}

/************************************
 * Function takes a ADC value and works out the voltage to 2 dp
 * the result is stored in buf as ascii text ready for display on LCD
 * Note result is stored in a buffer using pointers, it is not sent to the LCD
 ************************************/
void time2String(char *buf,unsigned int h, unsigned int s,unsigned int d,unsigned int m,unsigned int y) {
    //code to calculate the inegeter and fractions part of a ADC value
    // and format as a string using sprintf (see GitHub readme)
//    int int_part=ADC_val/77; // i.e. 255 / 5V = 51
//    int frac_part=(ADC_val*100)/77 - int_part*100;
   
    sprintf(buf,"%d:%d:%d %d-%d-%d ",h, s/60, s,d,m,y);
    //sprintf(buf,"%d %d ",SS, SR);
    LCD_sendstring(buf);
    __delay_ms(1000);
    
//    LCD_sendbyte(0b00000001,0);
//    __delay_ms(50);
}
//void date2String(char *str, unsigned int d, unsigned int m,unsigned int y)
//{
//    sprintf(str,"%d-%02d-%03d",d,m,y);
//    LCD_sendstring(str);
//    __delay_ms(1000);
//    
////    LCD_sendbyte(0b00000001,0);
////    __delay_ms(500);
//}