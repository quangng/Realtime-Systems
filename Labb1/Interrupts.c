#include "Interrupts.h"
#include "Serial.h"

void IRQHandler();
void *IRQHandlerTable[96];
void hang();

void CrashHandler()
{
	register uint32_t lr __asm("lr");
	volatile uint32_t address=lr;
	PrintSerialString("*** Crash at address 0x");
	PrintSerialHexWord(address);
	PrintSerialString(" ***\r\n");
	for(;;);
}

void InstallInterruptHandlers()
{
	*((uint32_t *)0x4020ffc8)=0xe59ff014;
	*((uint32_t *)0x4020ffcc)=0xe59ff014;
	*((uint32_t *)0x4020ffd0)=0xe59ff014;
	*((uint32_t *)0x4020ffd4)=0xe59ff014;
	*((uint32_t *)0x4020ffd8)=0xe59ff014;
	*((uint32_t *)0x4020ffdc)=0xe59ff014;
	*((uint32_t *)0x4020ffe0)=0xe59ff014;
	*((void **)0x4020ffe4)=CrashHandler;
	*((void **)0x4020ffe8)=CrashHandler;
	*((void **)0x4020ffec)=CrashHandler;
	*((void **)0x4020fff0)=CrashHandler;
	*((void **)0x4020fff4)=CrashHandler;
	*((void **)0x4020fff8)=IRQHandler;
	*((void **)0x4020fffc)=CrashHandler;

	// Mask out all interrupts
	INTCPS_MIR(0)=0xffffffff;
	INTCPS_MIR(1)=0xffffffff;
	INTCPS_MIR(2)=0xffffffff;

	// Acknowledge any spurious interrupts that may have been caused by the bootloader
	INTCPS_CONTROL=0x01;
}

void SetIRQHandler(int irq,void (*func)())
{
	IRQHandlerTable[irq]=func;
}

void EnableInterrupts()
{
	uint32_t temp=0x90;

	__asm volatile("mrs %0, cpsr\n"
	             "bic %0, %0, #0x80\n"
	             "msr cpsr_c, %0"
	             :"=r" (temp)
	             ::"memory");
}

bool DisableInterrupts()
{
	uint32_t old,temp;
	__asm volatile("mrs %0, cpsr\n"
	             "orr %1, %0, #0xc0\n"
	             "msr cpsr_c, %1"
	             :"=r" (old),"=r" (temp)
	             ::"memory");

	return (old&0x80)==0;
}

