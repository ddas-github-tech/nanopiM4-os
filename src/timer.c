#include "timer.h"
#include "printf.h"
#include "irq.h"

unsigned long jiffies = 0;
timer_registers* timer_reg;

static inline void disable_timer( timer_registers* timer_reg )
{
	setclr_reg32_bits(&timer_reg->timer_controlreg, TIMER_MASK,
			  TIMER_DISABLE);
}

static inline void enable_timer( timer_registers* timer_reg )
{
	setclr_reg32_bits(&timer_reg->timer_controlreg, TIMER_MASK,
			  TIMER_ENABLE);
}

static inline void set_timer_mode( timer_registers* timer_reg, uint32_t mode)
{
	setclr_reg32_bits(&timer_reg->timer_controlreg, MODE_MASK, mode);
}

static inline void mask_interrupt( timer_registers* timer_reg )
{
	setclr_reg32_bits(&timer_reg->timer_controlreg, INTR_MASK,
			  INTR_DISABLE);
}

static inline void unmask_interrupt( timer_registers* timer_reg )
{
	setclr_reg32_bits(&timer_reg->timer_controlreg, INTR_MASK,
			  INTR_ENABLE);
}

static inline void load_timer_value( timer_registers* timer_reg,
				    uint32_t timer_val )
{
	setclr_reg32_bits(&timer_reg->timer_load_count0, TIMER_LOAD_MASK,
			  timer_val);
}

static inline void clear_interrupt( timer_registers* timer_reg )
{
	setclr_reg32_bits(&timer_reg->timer_intstatus, INTR_STATUS_MASK,
			  INTR_CLR);
}

void timer_handler( void* irq_data )
{
	jiffies++;
	timer_registers* timer_reg = (timer_registers*) irq_data;
	clear_interrupt(timer_reg);
	deactivate_interrupt(TIMER0_IRQ);
	timer_tick();
	//printf("timer interrupt handler called\r\n");
	
}

void timer_init( void )
{
	timer_reg = (timer_registers*) TIMER_BASE0_5;
	
	disable_timer(timer_reg);
	clear_interrupt(timer_reg);
	mask_interrupt(timer_reg);
	set_timer_mode(timer_reg, FREE_RUNNING_MODE);
	//load_timer_value(timer_reg, (SECONDS/HZ));
	load_timer_value(timer_reg, (SECONDS));
	request_irq(TIMER0_IRQ, IRQ_TYPE_LEVEL, timer_handler, (void*)timer_reg);
	unmask_interrupt(timer_reg);
	enable_timer(timer_reg);
}
