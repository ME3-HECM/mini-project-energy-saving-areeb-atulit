#ifndef _comparator_H
#define _comparator_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void DAC_init(void);
void Comp1_init_rising_edge(void);
void Comp1_init_falling_edge(void);
#endif
