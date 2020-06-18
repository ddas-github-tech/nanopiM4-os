#include "gpio_led.h"
#include "printf.h"
#include "utils.h"
#include "uart.h"
#include "gic.h"
#include "irq.h"
#include "irq_test.h"

void kernel_main(void)
{
	int el;
	gpio_led_init();
	gpio_led_on();
	uart_init();
	uart_send_string("Hello, world!\n");
	init_printf(0, putc);
	el = get_el();
	printf("Hello World\n");
	printf("Exception level: %d \r\n", el);
	irq_vector_init();
	gic_init();
	//test_irq();
	timer_init();
	unmask_irq();

	while (1) {
		uart_send(uart_recv());
	}
}
