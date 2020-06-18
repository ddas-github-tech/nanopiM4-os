#include "irq_test.h"
#include "irq.h"
#include "printf.h"

void irq_test_handler( void* irq_data )
{
	printf("test interrupt handler called\r\n");
}

void test_irq( void )
{
	request_irq(IRQ_TEST, IRQ_TYPE_LEVEL, irq_test_handler, (void*) 0);
	generate_irq(IRQ_TEST);
}
