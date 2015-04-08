
///
/// \file
/// Assembly code for the interrupt handler.
/// 

.align 4

.global IRQHandler
IRQHandler:
	// Save the critical context
	stmfd	sp!,{r0-r12,lr}		// Save working registers and the Link register
	mrs		r11,spsr			// Save the SPSR into R11

	// Get the number of the highest priority active IRQ/FIQ
	ldr		r10,INTCPS_SIR_IRQ_ADDR
	ldr		r10,[r10]
	and		r10,r10,#0x7F

    // Load relevant subroutine handler
    ldr		r10,[pc,r10,lsl #2]	// PC base address points this instruction + 8
    b		invoke				// One instruction for padding

	// Table of 96 handler start addresses
.global IRQHandlerTable
IRQHandlerTable:
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang
	.word	hang,hang,hang,hang,hang,hang,hang,hang,hang,hang 
	.word	hang,hang,hang,hang,hang,hang

invoke:
	blx		r10

	// Allow new IRQs/FIQs at INTC side
	// The INTCPS_CONTROL register is a write only register so no need to write back others bits
	mov		r0,#0x01
	ldr		r1,INTCPS_CONTROL_ADDR
	str		r0,[r1]				// Write the NEWIRQAGR bit to allow new IRQs/FIQs

	// Data Synchronization Barrier
	mov		r0,#0
	mcr		p15,#0,r0,c7,c10,#4

	// Restore critical context
	msr		spsr,r11			// Restore the SPSR from R11
	ldmfd	sp!,{r0-r12,lr}		// Restore working registers and Link register

    // Return after handling the interrupt
	subs	pc,lr,#4

INTCPS_SIR_IRQ_ADDR:	.word 0x48200040
INTCPS_CONTROL_ADDR:	.word 0x48200048

.global hang
hang:
	nop
	nop


