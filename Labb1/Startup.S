	.section .startup,"x"
	.extern main
	.extern _stack
	.extern _data
	.extern _edata
	.extern _idata
	.extern _bss
	.extern _ebss

	#define IRQStackSize 1024
	#define FIQStackSize 1024
	#define SWIStackSize 1024

	.globl EntryPoint
EntryPoint:
	ldr		r0,=_stack

	// Set IRQ stack.
	msr		cpsr_c,#0xd2
	mov		sp,r0
	sub		r0,#IRQStackSize

	// Set FIQ stack.
	msr		cpsr_c,#0xd1
	mov		sp,r0
	sub		r0,#FIQStackSize

	// Set SWI stack.
	msr		cpsr_c,#0xd3
	mov		sp,r0
	sub		r0,#SWIStackSize

	// Set system stack.
	msr		cpsr_c,#0xdf
	mov		sp,r0

	// Switch back to SWI mode.
	msr		cpsr_c,#0xd3

	// Clear BSS segment.
	ldr		r0,=_bss
	ldr		r1,=_ebss
	movs	r3,#0
ClearBSS:
	str		r3,[r0],#4
	cmp		r0,r1
	blt		ClearBSS

	// Copy data segment.
/*	ldr		r0,=_data
	ldr		r1,=_edata
	ldr		r2,=_idata
CopyData:
	ldr		r3,[r2],#4
	str		r3,[r0],#4
	cmp		r0,r1
	blt		CopyData*/

	// Call main entry point.
	mov		r0,#0
	mov		r1,#0
	bl		main

End:
	b		End

