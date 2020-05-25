#include "utils.h"
#include "peripherals/gpio.h"

void gpio_led_init(void)
{
	unsigned int reg_val;
	reg_val = get32(PMUGRF_GPIO0B_IOMUX);
	reg_val &= ~(FUNC_MASK << GPIO0B4_SHIFT);
	reg_val |= (GPIO_FUNC << GPIO0B4_SHIFT);
	put32(PMUGRF_GPIO0B_IOMUX, reg_val);
}

void gpio_led_on(void)
{
	unsigned int reg_val;
	reg_val = get32(GPIO0_SWPORTA_DDR);
	reg_val |= (GPIO_OUT << GPIO0_13_SHIFT);
	put32(GPIO0_SWPORTA_DDR, reg_val);
	reg_val = get32(GPIO0_SWPORTA_DR);
	reg_val |= (GPIO_LED_ON << GPIO0_13_SHIFT);
	put32(GPIO0_SWPORTA_DR, reg_val);
}
