#ifndef _BITOPS_H
#define _BITOPS_H
#include <stdint.h>
#include <utils.h>

#define __stringify_1(x...)     #x
#define __stringify(x...)       __stringify_1(x)
#define isb() asm volatile("isb" : : : "memory")

#define read_sysreg(r) ( {                                       \
        uint64_t __val;                                              \
        asm volatile("mrs %0, " __stringify(r) : "=r" (__val)); \
	isb();							\
        __val;                                                  \
} )

/*
 * The "Z" constraint normally means a zero immediate, but when combined with
 * the "%x0" template means XZR.
 */
#define write_sysreg(v, r) do {                                 \
        uint64_t __val = (uint64_t)(v);                                   \
        asm volatile("msr " __stringify(r) ", %x0"              \
                     : : "rZ" (__val));                         \
	isb();							\
} while (0)



#define read_reg32_bits(r, n, s) ( { \
	uint32_t _val; \
	_val = get32((unsigned long)r); \
	_val &= (n << s);\
	_val >>= s;\
	_val;\
} )

#define setclr_reg32_bits(r, m, v) do { \
        uint32_t _val; \
        _val = get32((unsigned long)r); \
        _val = (_val & (~m)) | v; \
        put32((unsigned long)r, _val); \
} while (0)

#define setclr_reg64_bits(r, m, v) do { \
        uint64_t _val; \
        _val = get64((uint64_t)r); \
        _val = (_val & (~m)) | v; \
        put64((uint64_t)r, _val); \
} while (0)
 
#endif
