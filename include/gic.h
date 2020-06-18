#ifndef _GIC_H
#define _GIC_H
#include "peripherals/gic.h"

typedef enum {
	IRQ_TYPE_LEVEL = 0,
	IRQ_TYPE_EDGE  = 1
} irq_type_t;

enum {
	DISABLE_IRQ,
	ENABLE_IRQ
};

void gic_init( void );
void deactivate_interrupt( unsigned int );
void generate_irq( unsigned int );
void disable_irq( unsigned int );
void enable_irq( unsigned int, irq_type_t );
unsigned int get_pending_interrupt( void );

#endif /* _GIC_H */
