#include "gpio_led.h"
#include "utils.h"

void kernel_main(void)
{
	gpio_led_init();
	gpio_led_on();
}
