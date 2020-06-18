#include "mm.h"
#include "arm/sysregs.h"

.section ".text.boot"

.globl _start

_start:
//    bl      	led_on
	bl	el2_setup
el1_entry:
	adr	x0, bss_begin
	adr    	x1, bss_end
	sub    	x1, x1, x0
	bl     	memzero
	ldr    	x0, =(STACK_PTR)
	and    	sp, x0, #0xfffffffffffffff0
	bl    	kernel_main
hang:
    b		hang
    
el2_setup:
	mrs	x0, ICC_SRE_EL2
	ldr	x10, =ICC_SRE_EL2_VAL    // Set ICC_SRE_EL2.SRE & Enable ==1
	orr	x0, x0, x10    // Set ICC_SRE_EL2.SRE & Enable ==1
	msr	S3_4_C12_C9_5, x0
	isb                    // Make sure SRE is now set
	ldr     x0, =(SCTLR_VALUE_MMU_DISABLED) // disbale MMU, CACHES for EL1        
	msr     sctlr_el1, x0
	ldr     x0, =(HCR_VALUE) // configure 64bit EL1
	msr     hcr_el2, x0
	ldr     x0, =(SPSR_VALUE) // prepare SPSR to return to EL1
	msr     spsr_el2, x0
	msr     elr_el2, lr // jump to lr in EL1
	eret

led_on:
    mov     	x0, #0x4                        // #4
    movk    	x0, #0xff32, lsl #16
    ldr     	w1, [x0]
    dmb     	sy
    and     	w1, w1, #0xfffffcff
    dmb     	sy
    mov     	x19, #0x4                       // #4
    str     	w1, [x0]
    movk    	x19, #0xff72, lsl #16
    ldr     	w1, [x19]
    dmb     	sy
    orr     	w1, w1, #0x2000
    dmb     	sy
    mov     	x20, #0xff720000                // #4285661184
    str     	w1, [x19]
    ldr     	w1, [x20]
    dmb     	sy
    orr     	w1, w1, #0x2000
    dmb     	sy
    str     	w1, [x20]
    dmb	    	sy
    ret    
