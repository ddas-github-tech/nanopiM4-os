#include "utils.h"
#include "peripherals/uart.h"

void uart_send ( char c )
{
	while(!(get32(UART2_LSR) & UART_LSR_THRE)) {
	}
	put32(UART2_THR,c);
}

char uart_recv ( void )
{
    while(1) {
        if(get32(UART2_LSR)&0x01)
            break;
    }
    return(get32(UART2_THR)&0xFF);
}

void uart_send_string(char* str)
{
	char c;
	while (*str) {
		if (*str == '\n')
			c = '\r';
		else
			c = *str;
		uart_send(c);
		str++;
	}
}

void uart_init ( void )
{
	unsigned int selector;

	/* set IOMUX as UART2C */
	selector = get32(GRF_GPIO4C_IOMUX);
	selector &= ~(15<<6);                   // clean [9:6]
	selector |= 5<<6;                      // set 4b'0101 select UART2C IN/OUT
	// put32(GRF_GPIO4C_IOMUX,selector);
	put32(GRF_GPIO4C_IOMUX,0x03c00140);


	/* Set channel C as UART2 input */
	selector = get32(GRF_SOC_CON7);
	selector &= ~(3 << 10);
	selector |= 2 << 10;
	put32(GRF_SOC_CON7,selector);


	put32(UART2_IER, DISABLE_INTR);
	put32(UART2_MCR, UART_MCRVAL);
	put32(UART2_FCR, UART_FCR_DEFVAL);
        put32(UART2_LCR, UART_LCR_BKSE | UART_LCRVAL);
        put32(UART2_DLL, UART2_1_5_MBPS_DIVISOR & 0xff);
        put32(UART2_DLM, (UART2_1_5_MBPS_DIVISOR >> 8) & 0xff);
        put32(UART2_LCR, UART_LCRVAL);
	put32(UART2_MCR, UART_MCRVAL);
}

// This function is required by printf function
void putc ( void* p, char c)
{
	uart_send(c);
}
