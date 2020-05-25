#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "base.h"

#define GRF_GPIO4C_IOMUX	(GRF_BASE + 0x0E028)
#define PMUGRF_GPIO0B_IOMUX	(PMUGRF_BASE + 0x0004)
#define GPIO0B5_SHIFT		8
#define FUNC_MASK		0x03
#define GPIO_FUNC		0x00
#define GPIO0_BASE		(PBASE + 0x7720000)
#define GPIO0_SWPORTA_DR	(GPIO0_BASE + 0x0000)
#define GPIO0_SWPORTA_DDR	(GPIO0_BASE + 0X0004)
#define GPIO0_13_SHIFT		13
#define GPIO_OUT		1
#define GPIO_IN			0
#define GPIO_LED_ON		1
#define GPIO_LED_OFF		0
#define GPFSEL1         	(PBASE + 0x00200004)
#define GPSET0          	(PBASE + 0x0020001C)
#define GPCLR0          	(PBASE + 0x00200028)
#define GPPUD           	(PBASE + 0x00200094)
#define GPPUDCLK0       	(PBASE + 0x00200098)

#endif  /*_P_GPIO_H */
