#ifndef	_BOOT_H
#define	_BOOT_H
#include <stdint.h>

extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
extern void put64 ( uint64_t, uint64_t );
extern uint64_t get64 ( uint64_t );
extern unsigned int get_el ( void );

#endif  /*_BOOT_H */
