#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

///
/// \file
/// Functions for installing IRQ handlers, and and macros for the
/// interrupt control registers. See the OMAP3 documentation for more
/// information about how to use these.
///

#include <stdint.h>
#include <stdbool.h>

#include "Registers.h"

#define INTCPS_SYSCONFIG REG(0x48200010)
#define INTCPS_SYSSTATUS REG(0x48200014)
#define INTCPS_SIR_IRQ REG(0x48200040)
#define INTCPS_SIR_FIQ REG(0x48200044)
#define INTCPS_CONTROL REG(0x48200048)
#define INTCPS_PROTECTION REG(0x4820004C)
#define INTCPS_IDLE REG(0x48200050)
#define INTCPS_IRQ_PRIORITY REG(0x48200060)
#define INTCPS_FIQ_PRIORITY REG(0x48200064)
#define INTCPS_THRESHOLD REG(0x48200068)

#define INTCPS_ITR(n) REG(0x48200080+0x20*(n))
#define INTCPS_MIR(n) REG(0x48200084+0x20*(n))
#define INTCPS_MIR_CLEAR(n) REG(0x48200088+0x20*(n))
#define INTCPS_MIR_SET(n) REG(0x4820008C+0x20*(n))
#define INTCPS_ISR_SET(n) REG(0x48200090+0x20*(n))
#define INTCPS_ISR_CLEAR(n) REG(0x48200094+0x20*(n))
#define INTCPS_PENDING_IRQ(n) REG(0x48200098+0x20*(n))
#define INTCPS_PENDING_FIQ(n) REG(0x4820009C+0x20*(n))
#define INTCPS_ILR(m) REG(0x48200100+4*(m))

///
/// Install the IRQ multiplexer. Allows separate handlers to be
/// installed for all the numbered IRQs. Also sets all interrupt mask
/// bits, disabling all interrupt sources, and acknowledges any pending
/// interrupts. Must be called at the start of the program before
/// trying to use interrupts.
///

void InstallInterruptHandlers();

///
/// Set the handler subroutine for a given IRQ. This function will be
/// called when this specific IRQ occurs.
///
/// \param irq The number of the IRQ.
/// \param func The function that will handle this IRQ. This function
///             will be called in an interrupt context with the (not
///             very big) interrupt stack. It should finish quickly,
///             and avoid using much stack space. It should also make
///             sure to acknowledge the interrupt flag in whatever
///             peripheral caused the IRQ, or else it will get called
///             again immediately when it exits.
///

void SetIRQHandler(int irq,void (*func)());

///
/// Enable interrupts globally. Must be called at the start of the
/// program, as interrupts are disabled at startup.
///

void EnableInterrupts();

///
/// Disable interrupts globally.
///

bool DisableInterrupts();

#endif

