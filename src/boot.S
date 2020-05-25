.section ".text.boot"

.globl _start

_start:
    bl      led_on
hang:
    b	   hang
 
led_on:
    mov     x0, #0x4                        // #4
    movk    x0, #0xff32, lsl #16
    ldr     w1, [x0]
    dmb     sy
    and     w1, w1, #0xfffffcff
    dmb     sy
    mov     x19, #0x4                       // #4
    str     w1, [x0]
    movk    x19, #0xff72, lsl #16
    ldr     w1, [x19]
    dmb     sy
    orr     w1, w1, #0x2000
    dmb     sy
    mov     x20, #0xff720000                // #4285661184
    str     w1, [x19]
    ldr     w1, [x20]
    dmb     sy
    orr     w1, w1, #0x2000
    dmb     sy
    str     w1, [x20]
    dmb	    sy
    ret 
