#ifndef _Functions_H
#define _Functions_H
#include <xc.h>
#define _XTAL_FREQ 64000000
//function prototypes
void streetLightInit(void);
void increment();
void poweroff();
void day1_init();
int sunrise();
int sunset();
void timeadjuster(int sunrise_time,int sunset_time);
void daylightsavings();
#endif