#ifndef	_MM_H
#define	_MM_H

#define KERNEL_LOAD_ADDR		(0x02080000)
#define MAX_KERNEL_SIZE			(0x01000000)
#define STACK_SIZE			(0x01000000)
#define STACK_PTR	              	(KERNEL_LOAD_ADDR + MAX_KERNEL_SIZE + \
					 STACK_SIZE)
#define PAGE_SHIFT			(12)
#define PAGE_SIZE			(1 << PAGE_SHIFT)	
#define MEM_POOL_SIZE			(0x40000000)
#define MEM_HOLE			(PAGE_SIZE)
#define LOW_MEMORY			(STACK_PTR + MEM_HOLE)
#define HIGH_MEMORY			(LOW_MEMORY + MEM_POOL_SIZE)
#define PAGING_MEMORY			(HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES			(PAGING_MEMORY/PAGE_SIZE)

#ifndef __ASSEMBLER__

unsigned long get_free_page();
void free_page(unsigned long p);
void memzero(unsigned long src, unsigned long n);

#endif

#endif  /*_MM_H */
