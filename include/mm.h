#ifndef	_MM_H
#define	_MM_H

#define KERNEL_LOAD_ADDR		(0x02080000)
#define MAX_KERNEL_SIZE			(0x10000000)
#define STACK_PTR	              	(KERNEL_LOAD_ADDR + MAX_KERNEL_SIZE)

#ifndef __ASSEMBLER__

void memzero(unsigned long src, unsigned long n);

#endif

#endif  /*_MM_H */
