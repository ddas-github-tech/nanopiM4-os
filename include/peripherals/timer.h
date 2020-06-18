#ifndef _PTIMER_H
#define _PTIMER_H
#include "base.h"
#include <stdint.h>

typedef volatile struct __attribute__((packed)) {
	uint32_t timer_load_count0;
	uint32_t timer_load_count1;
	uint32_t timer_current_value0;
	uint32_t timer_current_value1;
	uint32_t timer_load_count2;
	uint32_t timer_load_count3;
	uint32_t timer_intstatus;
	uint32_t timer_controlreg;
} timer_registers;


#define TIMER_BASE0_5		(PBASE + 0x7850000)
#define TIMER_SHIFT		0
#define TIMER_DISABLE 		(0 << TIMER_SHIFT)
#define TIMER_ENABLE 		(1 << TIMER_SHIFT)
#define TIMER_MASK		(1 << TIMER_SHIFT)
#define MODE_SHIFT		1
#define FREE_RUNNING_MODE 	(0 << MODE_SHIFT)
#define USER_DEFINED_MODE 	(1 << MODE_SHIFT)
#define	MODE_MASK		(1 << MODE_SHIFT)
#define INTR_MASK_SHIFT		2
#define	INTR_MASK		(1 << INTR_MASK_SHIFT)
#define	INTR_ENABLE		(1 << INTR_MASK_SHIFT)
#define INTR_DISABLE		(0 << INTR_MASK_SHIFT)
/* timer clock is 24MHz */
#define SECONDS			24000000
#define INTR_STATUS_MASK	(1 << 0)
#define INTR_CLR		1
#define TIMER_LOAD_MASK		0xFFFFFFFF

#endif
