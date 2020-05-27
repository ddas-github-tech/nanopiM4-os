
.globl put32
put32:
	dmb sy
	str w1,[x0]
	ret

.globl get32
get32:
	ldr w0,[x0]
	dmb sy
	ret

.global get_el
get_el:
	mrs x0, currentEL
	lsr x0, x0, #2
	ret
