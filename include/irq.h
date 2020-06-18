#ifndef	_IRQ_H
#define	_IRQ_H
#include "gic.h"
#include "bitops.h"

#define irq_vector_init() do {			\
	asm volatile("adr     x0, vectors ");	\
	asm volatile("msr     vbar_el1, x0");	\
	isb();					\
} while (0)

#define unmask_irq() do {			\
	asm volatile("msr    daifclr, #2");	\
	isb();					\
} while (0)			

#define mask_irq() do {				\
	asm volatile("msr    daifset, #2");	\
	isb();					\
} while (0)					\

extern void (*call_handler[MAX_SPI])(void *);
extern void* handler_args[MAX_SPI];
void request_irq( unsigned int irq_no, irq_type_t, void (* )( void* ), void* );

#endif  /*_IRQ_H */
