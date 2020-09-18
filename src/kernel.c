#include "gpio_led.h"
#include "printf.h"
#include "utils.h"
#include "uart.h"
#include "gic.h"
#include "irq.h"
#include "irq_test.h"
#include "fork.h"
#include "sched.h"
#include "timer.h"

void process(char *arg)
{
	while (1){
		printf("Process: %s\r\n", arg); 
		printf("vruntime of the current: %u is  %u\r\n", current->id, current->vruntime);
		printf("Jiffies:  %u\r\n", jiffies);
	}
} 

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

	int res = copy_process((unsigned long)&process, "AAAA");
	if (res != 0) {                                                         
		printf("error while starting process 1\r\n");                       
		return;                                                         
        }                                                                       
        res = copy_process((unsigned long)&process, "BBBB");    
        if (res != 0) {                                                         
                printf("error while starting process 2\r\n");                       
                return;                                                         
        }

	timer_init();
	unmask_irq();
	while (1) {
		uart_send(uart_recv());
	}
}
