#ifndef _TIMER_H
#define _TIMER_H

#include "peripherals/timer.h"
#include "bitops.h"
extern unsigned long jiffies;

#define HZ			(10000)
#define jiffies_to_sec(j)	(j / HZ)
#define jiffies_to_msec(j)	(j / 1000)
#define jiffies_to_usec(j)	(j * 100)
#define jiffies_to_nsec(j)	(j * 100 * 1000)

void timer_handler( void* );
void timer_init( void );
extern void timer_tick( void );

#define TIMER0_IRQ 113

#endif
