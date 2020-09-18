#include "printf.h"
#include "entry.h"
#include "irq.h"

/* array of funcion pointers to hold handlers */
void (*call_handler[MAX_SPI])(void *) = { 0UL };

/* array of void * to pass args to handlers */
void* handler_args[MAX_SPI] = {  0UL };

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_irq(void)
{
	unsigned int irq;

	irq = get_pending_interrupt();

	printf("pending irq:%d \r\n", irq);
	if (call_handler[irq - SPI_OFFSET])
		call_handler[irq - SPI_OFFSET](handler_args[irq - SPI_OFFSET]);
	else
		printf("Unknown pending irq: \r\n");
	//deactivate_interrupt(irq);

}

void request_irq( unsigned int irq_no, irq_type_t type, void (* irq_handler)( void* ), void* args )
{
	call_handler[irq_no - SPI_OFFSET] = irq_handler;
	handler_args[irq_no - SPI_OFFSET] = args;
	enable_irq(irq_no, type);
}
