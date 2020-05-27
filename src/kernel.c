#include "gpio_led.h"
#include "printf.h"
#include "utils.h"
#include "uart.h"

void kernel_main(void)
{
	int el;
	init_printf(0, putc);
	el = get_el();
	printf("Exception level: %d \r\n", el);
	gpio_led_init();
	gpio_led_on();
	uart_init();
	uart_send_string("Hello, world!\n");
	while (1) {
		uart_send(uart_recv());
	}
}
