#ifndef _TIMER_H
#define _TIMER_H

#include "peripherals/timer.h"
#include "bitops.h"

void timer_handler( void* );
void timer_init( void );

#define TIMER0_IRQ 113

#endif
