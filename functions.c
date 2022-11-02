/*
 * File:   functions.c
 * Author: 44756
 *
 * Created on October 31, 2022, 11:49 PM
 */


#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "functions.h"

void incrementseconds(int seconds)
{
    seconds++;
    LEDarray_disp_bin(seconds);
}