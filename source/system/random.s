
.include "defs.hs"

.section .text

.globl hw_random_init
hw_random_init:

	ldr r0, =HW_RNG_STATUS
	ldr r1, =HW_RNG_WARMUP_COUNT
	str r1, [r0]
	ldr r0, =HW_RNG_CTRL
	ldr r1, =HW_RNG_CTRL_EN
	str r1, [r0]

	mov pc, lr

.globl hw_random_int32
hw_random_int32:

	ldr r0, =HW_RNG_STATUS
w1:
	ldr r1, [r0]
	lsrs r1, #24
	beq w1

	ldr r1, =HW_RNG_DATA
	ldr r0, [r1]

	mov pc, lr
