#include "Leds.h"


#define CONTROL_PADCONF_UART1_TX_HIGH ((volatile uint16_t *)(0x4800217C + 0x2))
#define CONTROL_PADCONF_UART1_CTS_LOW ((volatile uint16_t *)(0x48002180))

/* Clock registers */
#define CM_FCLKEN_PER ((volatile uint32_t *)(0x48005000))
#define CM_ICLKEN_PER ((volatile uint32_t *)(0x48005010))
#define CM_ICLKEN_WKUP ((volatile uint32_t *)(0x48004C10))
#define EN_GPIO5 (1<<16)
#define EN_CLK32 (1<<2)

/* GPIO regs */
#define OMAP34XX_GPIO5_BASE ((volatile uint32_t *)(0x49056000))

#define GPIO_CTRL	(0x30/4)
#define GPIO_OE		(0x34/4)
#define GPIO_DATAO	(0x3C/4)
#define GPIO_SET	(0x94/4)
#define GPIO_CLR	(0x90/4)

#define GPIO_ENABLE	0x01

void InitLeds()
{
	/* LED Control Logic (Start) */
	/*
	 * There are 2 LEDs on Beagle
	 * USR0=D6=LED0_GPIO150 on Ball W8 - uart1_cts = 0x48002180(LOW)
	 * USR1=D7=LED1_GPIO149 on Ball AA9 - uart1_rts= 0x4800217C(HIGH)
	 * Need to do two things:
	 * a) pin mux it to the right point
	 * b) Enable I/F clks to GPIO, Enable GPIO,
	 * Enable Pin Mux Pull high to force a glow
	 * Do a half word access to update 16 bit part of the reg
	 */
	*CONTROL_PADCONF_UART1_TX_HIGH=4;
	*CONTROL_PADCONF_UART1_CTS_LOW=4;

	/* Both GPIO 149 and 150 fall into GPIO5 module.
	 * Enable I and F Clocks for GPIO5 */

	*CM_FCLKEN_PER|=EN_GPIO5;
	*CM_ICLKEN_PER|=EN_GPIO5;

	/* Setup Blinky LEDs */

	/* Enable the Module First */
	OMAP34XX_GPIO5_BASE[GPIO_CTRL]|=GPIO_ENABLE;
	OMAP34XX_GPIO5_BASE[GPIO_OE]&=~(3<<21);
}

void SetLeds(int state)
{
	OMAP34XX_GPIO5_BASE[GPIO_DATAO]=state<<21;
}

