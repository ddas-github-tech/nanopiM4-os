#ifndef	_P_UART_H
#define	_P_UART_H

#include "base.h"

#define GRF_SOC_CON7		(GRF_BASE + 0x0e21C)
#define GRF_GPIO4C_IOMUX	(GRF_BASE + 0x0E028)

#define UART_RBR		0x00
#define UART_THR		0x00
#define UART_DLL		0x00
#define UART_DLM		0x04
#define UART_IER		0x04
#define UART_FCR		0x08
#define UART_LCR		0x0C
#define UART_MCR		0x10
#define UART_LSR		0x14

#define UART2_BASE	(PBASE + 0x71A0000)
#define UART2_RBR	(UART2_BASE+UART_RBR)
#define UART2_THR	(UART2_BASE+UART_THR)	
#define UART2_DLL	(UART2_BASE+UART_DLL)
#define UART2_DLM	(UART2_BASE+UART_DLM)
#define UART2_IER	(UART2_BASE+UART_IER)
#define UART2_FCR	(UART2_BASE+UART_FCR)
#define UART2_LCR	(UART2_BASE+UART_LCR)
#define UART2_MCR	(UART2_BASE+UART_MCR)
#define UART2_LSR	(UART2_BASE+UART_LSR)

/*
 * These are the definitions for the Modem Control Register
 */
#define UART_MCR_DTR    0x01            /* DTR   */
#define UART_MCR_RTS    0x02            /* RTS   */

/*
 * These are the definitions for the FIFO Control Register
 */ 
#define UART_FCR_FIFO_EN        0x01 /* Fifo enable */
#define UART_FCR_RXSR           0x02 /* Receiver soft reset */
#define UART_FCR_TXSR           0x04 /* Transmitter soft reset */

/*
 * These are the definitions for the Line Status Register
 */
#define UART_LSR_THRE   0x20            /* Xmit holding register empty */

/*
 * These are the definitions for the Line Control Register
 *
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
/* useful defaults for LCR */
#define UART_LCR_8N1    0x03
#define UART_LCR_BKSE   0x80            /* Bank select enable */

#define DISABLE_INTR		0x00
#define UART_MCRVAL (UART_MCR_DTR | \
                     UART_MCR_RTS)              /* RTS/DTR */

/* Clear & enable FIFOs */
#define UART_FCR_DEFVAL (UART_FCR_FIFO_EN | \
                        UART_FCR_RXSR | \
                        UART_FCR_TXSR)

#define UART2_1_5_MBPS_DIVISOR	0x0001	/* divisor for 1.5mbps with 2.4Mhz clk */
#define UART_LCRVAL UART_LCR_8N1                /* 8 data, 1 stop, no parity */

#define UART2C_MASK		15
#define UART2C_SHIFT 		6
#define UART2C_ENABLE_SHIFT	(16 + UART2C_SHIFT)
#define UART2C_VAL		5
#define UART_CHAN_MASK		3
#define UART_CHAN_SHIFT		10
#define UART2C_CHAN		2

#endif  /*_P_UART_H */
