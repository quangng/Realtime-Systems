/*
 * (C) Copyright 2006
 * Texas Instruments, <www.ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#ifndef _OMAP34XX_CPU_H
#define  _OMAP34XX_CPU_H

///
/// \file
///
/// Macros used internally by I2C.c.
///

/*---------------#include "omap3.h"---------------*/

/*
 * (C) Copyright 2006
 * Texas Instruments, <www.ti.com>
 * Richard Woodruff <r-woodruff2@ti.com>
 * Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * 3430 specific Section
 */

/* Stuff on L3 Interconnect */
#define SMX_APE_BASE			0x68000000

/* L3 Firewall */
#define A_REQINFOPERM0		(SMX_APE_BASE + 0x05048)
#define A_READPERM0		(SMX_APE_BASE + 0x05050)
#define A_WRITEPERM0		(SMX_APE_BASE + 0x05058)

/* GPMC */
#define OMAP34XX_GPMC_BASE		(0x6E000000)

/* SMS */
#define OMAP34XX_SMS_BASE		0x6C000000

/* SDRC */
#define OMAP34XX_SDRC_BASE		0x6D000000

/*
 * L4 Peripherals - L4 Wakeup and L4 Core now
 */
#define OMAP34XX_CORE_L4_IO_BASE	0x48000000

#define OMAP34XX_WAKEUP_L4_IO_BASE	0x48300000

#define OMAP34XX_L4_PER			0x49000000

#define OMAP34XX_L4_IO_BASE		OMAP34XX_CORE_L4_IO_BASE

/* CONTROL */
#define OMAP34XX_CTRL_BASE		(OMAP34XX_L4_IO_BASE+0x2000)

/* TAP information  dont know for 3430*/
#define OMAP34XX_TAP_BASE		(0x49000000)	/*giving some junk for virtio */

/* UART */
#define OMAP34XX_UART1			(OMAP34XX_L4_IO_BASE+0x6a000)
#define OMAP34XX_UART2			(OMAP34XX_L4_IO_BASE+0x6c000)
#define OMAP34XX_UART3			(OMAP34XX_L4_PER+0x20000)

/* General Purpose Timers */
#define OMAP34XX_GPT1			0x48318000
#define OMAP34XX_GPT2			0x49032000
#define OMAP34XX_GPT3			0x49034000
#define OMAP34XX_GPT4			0x49036000
#define OMAP34XX_GPT5			0x49038000
#define OMAP34XX_GPT6			0x4903A000
#define OMAP34XX_GPT7			0x4903C000
#define OMAP34XX_GPT8			0x4903E000
#define OMAP34XX_GPT9			0x49040000
#define OMAP34XX_GPT10			0x48086000
#define OMAP34XX_GPT11			0x48088000
#define OMAP34XX_GPT12			0x48304000

/* WatchDog Timers (1 secure, 3 GP) */
#define WD1_BASE			(0x4830C000)
#define WD2_BASE			(0x48314000)
#define WD3_BASE			(0x49030000)

/* 32KTIMER */
#define SYNC_32KTIMER_BASE		(0x48320000)
#define S32K_CR				(SYNC_32KTIMER_BASE+0x10)

/* omap3 GPIO registers */
#define OMAP34XX_GPIO1_BASE		0x48310000
#define OMAP34XX_GPIO2_BASE		0x49050000
#define OMAP34XX_GPIO3_BASE		0x49052000
#define OMAP34XX_GPIO4_BASE		0x49054000
#define OMAP34XX_GPIO5_BASE		0x49056000
#define OMAP34XX_GPIO6_BASE		0x49058000

/*
 * SDP3430 specific Section
 */

/*
 *  The 343x's chip selects are programmable.  The mask ROM
 *  does configure CS0 to 0x08000000 before dispatch.  So, if
 *  you want your code to live below that address, you have to
 *  be prepared to jump though hoops, to reset the base address.
 *  Same as in SDP3430
 */
#if (CONFIG_3430SDP)

/* base address for indirect vectors (internal boot mode) */
#define SRAM_OFFSET0			0x40000000
#define SRAM_OFFSET1			0x00200000
#define SRAM_OFFSET2			0x0000F800
#define SRAM_VECT_CODE			(SRAM_OFFSET0|SRAM_OFFSET1|SRAM_OFFSET2)

#define LOW_LEVEL_SRAM_STACK		0x4020FFFC

/* FPGA on Debug board.*/
#define ETH_CONTROL_REG			(DEBUG_BASE+0x30b)
#define LAN_RESET_REGISTER		(DEBUG_BASE+0x1c)

#define DIP_SWITCH_INPUT_REG2		(DEBUG_BASE+0x60)
#define LED_REGISTER			(DEBUG_BASE+0x40)
#define FPGA_REV_REGISTER		(DEBUG_BASE+0x10)
#define EEPROM_MAIN_BRD			(DEBUG_BASE+0x10000+0x1800)
#define EEPROM_CONN_BRD			(DEBUG_BASE+0x10000+0x1900)
#define EEPROM_UI_BRD			(DEBUG_BASE+0x10000+0x1A00)
#define EEPROM_MCAM_BRD			(DEBUG_BASE+0x10000+0x1B00)
#define ENHANCED_UI_EE_NAME		"750-2075"

#elif (CONFIG_OMAP3_BEAGLE)

/* base address for indirect vectors (internal boot mode) */
#define SRAM_OFFSET0			0x40000000
#define SRAM_OFFSET1			0x00200000
#define SRAM_OFFSET2			0x0000F800
#define SRAM_VECT_CODE			(SRAM_OFFSET0|SRAM_OFFSET1|SRAM_OFFSET2)

#define LOW_LEVEL_SRAM_STACK		0x4020FFFC

#define DEBUG_LED1			149	/* gpio */
#define DEBUG_LED2			150	/* gpio */

#endif				/* endif (CONFIG_3430SDP)  */

/*------------------------------------------------*/

/* Register offsets of common modules */
/* Control */
#define CONTROL_STATUS			(OMAP34XX_CTRL_BASE + 0x2F0)
#define OMAP34XX_MCR			(OMAP34XX_CTRL_BASE + 0x8C)
#define CONTROL_SCALABLE_OMAP_STATUS	(OMAP34XX_CTRL_BASE + 0x44C)
#define CONTROL_SCALABLE_OMAP_OCP	(OMAP34XX_CTRL_BASE + 0x534)

/* Tap Information */
#define TAP_IDCODE_REG		(OMAP34XX_TAP_BASE+0x204)
#define PRODUCTION_ID		(OMAP34XX_TAP_BASE+0x208)

/* device type */
#define DEVICE_MASK		(BIT8|BIT9|BIT10)
#define TST_DEVICE		0x0
#define EMU_DEVICE		0x1
#define HS_DEVICE		0x2
#define GP_DEVICE		0x3

/* GPMC CS3/cs4/cs6 not avaliable */
#define GPMC_BASE		(OMAP34XX_GPMC_BASE)
#define GPMC_SYSCONFIG		(OMAP34XX_GPMC_BASE+0x10)
#define GPMC_IRQSTATUS		(OMAP34XX_GPMC_BASE+0x18)
#define GPMC_IRQENABLE		(OMAP34XX_GPMC_BASE+0x1C)
#define GPMC_TIMEOUT_CONTROL	(OMAP34XX_GPMC_BASE+0x40)
#define GPMC_CONFIG		(OMAP34XX_GPMC_BASE+0x50)
#define GPMC_STATUS		(OMAP34XX_GPMC_BASE+0x54)

#define GPMC_CONFIG_CS0		(OMAP34XX_GPMC_BASE+0x60)
#define GPMC_CONFIG_WIDTH	(0x30)

#define GPMC_CONFIG1		(0x00)
#define GPMC_CONFIG2		(0x04)
#define GPMC_CONFIG3		(0x08)
#define GPMC_CONFIG4		(0x0C)
#define GPMC_CONFIG5		(0x10)
#define GPMC_CONFIG6		(0x14)
#define GPMC_CONFIG7		(0x18)
#define GPMC_NAND_CMD		(0x1C)
#define GPMC_NAND_ADR		(0x20)
#define GPMC_NAND_DAT		(0x24)

#define GPMC_ECC_CONFIG		(0x1F4)
#define GPMC_ECC_CONTROL	(0x1F8)
#define GPMC_ECC_SIZE_CONFIG	(0x1FC)
#define GPMC_ECC1_RESULT	(0x200)
#define GPMC_ECC2_RESULT	(0x204)
#define GPMC_ECC3_RESULT	(0x208)
#define GPMC_ECC4_RESULT	(0x20C)
#define GPMC_ECC5_RESULT	(0x210)
#define GPMC_ECC6_RESULT	(0x214)
#define GPMC_ECC7_RESULT	(0x218)
#define GPMC_ECC8_RESULT	(0x21C)
#define GPMC_ECC9_RESULT	(0x220)

/* GPMC Mapping */
# define FLASH_BASE		0x10000000	/* NOR flash (aligned to 256 Meg) */
# define FLASH_BASE_SDPV1	0x04000000	/* NOR flash (aligned to 64 Meg) */
# define FLASH_BASE_SDPV2	0x10000000	/* NOR flash (aligned to 256 Meg) */
# define DEBUG_BASE		0x08000000	/* debug board */
# define NAND_BASE		0x30000000	/* NAND addr (actual size small port) */
# define PISMO2_BASE		0x18000000	/* PISMO2 CS1/2 */
# define ONENAND_MAP		0x20000000	/* OneNand addr (actual size small port */

/* SMS */
#define SMS_SYSCONFIG		(OMAP34XX_SMS_BASE+0x10)
#define SMS_RG_ATT0		(OMAP34XX_SMS_BASE+0x48)
#define SMS_CLASS_ARB0		(OMAP34XX_SMS_BASE+0xD0)
#define BURSTCOMPLETE_GROUP7	BIT31

/* SDRC */
#define SDRC_SYSCONFIG		(OMAP34XX_SDRC_BASE+0x10)
#define SDRC_STATUS		(OMAP34XX_SDRC_BASE+0x14)
#define SDRC_CS_CFG		(OMAP34XX_SDRC_BASE+0x40)
#define SDRC_SHARING		(OMAP34XX_SDRC_BASE+0x44)
#define SDRC_DLLA_CTRL		(OMAP34XX_SDRC_BASE+0x60)
#define SDRC_DLLA_STATUS	(OMAP34XX_SDRC_BASE+0x64)
#define SDRC_DLLB_CTRL		(OMAP34XX_SDRC_BASE+0x68)
#define SDRC_DLLB_STATUS	(OMAP34XX_SDRC_BASE+0x6C)
#define DLLPHASE		BIT1
#define LOADDLL			BIT2
#define DLL_DELAY_MASK		0xFF00
#define DLL_NO_FILTER_MASK	(BIT8|BIT9)

#define SDRC_POWER		(OMAP34XX_SDRC_BASE+0x70)
#define WAKEUPPROC		BIT26

#define SDRC_MCFG_0		(OMAP34XX_SDRC_BASE+0x80)
#define SDRC_MR_0		(OMAP34XX_SDRC_BASE+0x84)
#define SDRC_ACTIM_CTRLA_0	(OMAP34XX_SDRC_BASE+0x9C)
#define SDRC_ACTIM_CTRLB_0	(OMAP34XX_SDRC_BASE+0xA0)
#define SDRC_ACTIM_CTRLA_1	(OMAP34XX_SDRC_BASE+0xC4)
#define SDRC_ACTIM_CTRLB_1	(OMAP34XX_SDRC_BASE+0xC8)
#define SDRC_RFR_CTRL		(OMAP34XX_SDRC_BASE+0xA4)
#define SDRC_RFR_CTRL		(OMAP34XX_SDRC_BASE+0xA4)
#define SDRC_MANUAL_0		(OMAP34XX_SDRC_BASE+0xA8)
#define OMAP34XX_SDRC_CS0	0x80000000
#define OMAP34XX_SDRC_CS1	0xA0000000
#define CMD_NOP			0x0
#define CMD_PRECHARGE		0x1
#define CMD_AUTOREFRESH		0x2
#define CMD_ENTR_PWRDOWN	0x3
#define CMD_EXIT_PWRDOWN	0x4
#define CMD_ENTR_SRFRSH		0x5
#define CMD_CKE_HIGH		0x6
#define CMD_CKE_LOW		0x7
#define SOFTRESET		BIT1
#define SMART_IDLE		(0x2 << 3)
#define REF_ON_IDLE		(0x1 << 6)

/* timer regs offsets (32 bit regs) */
#define TIDR			0x0	/* r */
#define TIOCP_CFG		0x10	/* rw */
#define TISTAT			0x14	/* r */
#define TISR			0x18	/* rw */
#define TIER			0x1C	/* rw */
#define TWER			0x20	/* rw */
#define TCLR			0x24	/* rw */
#define TCRR			0x28	/* rw */
#define TLDR			0x2C	/* rw */
#define TTGR			0x30	/* rw */
#define TWPS			0x34	/* r */
#define TMAR			0x38	/* rw */
#define TCAR1			0x3c	/* r */
#define TSICR			0x40	/* rw */
#define TCAR2			0x44	/* r */
#define GPT_EN			((0<<2)|BIT1|BIT0)	/* enable sys_clk NO-prescale /1 */

/* Watchdog */
#define WWPS			0x34	/* r */
#define WSPR			0x48	/* rw */
#define WD_UNLOCK1		0xAAAA
#define WD_UNLOCK2		0x5555

/* PRCM */
#define CM_FCLKEN_IVA2      0x48004000
#define CM_CLKEN_PLL_IVA2   0x48004004
#define CM_IDLEST_PLL_IVA2  0x48004024
#define CM_CLKSEL1_PLL_IVA2 0x48004040
#define CM_CLKSEL2_PLL_IVA2 0x48004044
#define CM_CLKEN_PLL_MPU    0x48004904
#define CM_IDLEST_PLL_MPU   0x48004924
#define CM_CLKSEL1_PLL_MPU  0x48004940
#define CM_CLKSEL2_PLL_MPU  0x48004944
#define CM_FCLKEN1_CORE     0x48004a00
#define CM_ICLKEN1_CORE     0x48004a10
#define CM_ICLKEN2_CORE     0x48004a14
#define CM_CLKSEL_CORE      0x48004a40
#define CM_FCLKEN_GFX       0x48004b00
#define CM_ICLKEN_GFX       0x48004b10
#define CM_CLKSEL_GFX       0x48004b40
#define CM_FCLKEN_WKUP      0x48004c00
#define CM_ICLKEN_WKUP      0x48004c10
#define CM_CLKSEL_WKUP      0x48004c40
#define CM_IDLEST_WKUP      0x48004c20
#define CM_CLKEN_PLL        0x48004d00
#define CM_IDLEST_CKGEN     0x48004d20
#define CM_CLKSEL1_PLL      0x48004d40
#define CM_CLKSEL2_PLL      0x48004d44
#define CM_CLKSEL3_PLL      0x48004d48
#define CM_FCLKEN_DSS       0x48004e00
#define CM_ICLKEN_DSS       0x48004e10
#define CM_CLKSEL_DSS       0x48004e40
#define CM_FCLKEN_CAM       0x48004f00
#define CM_ICLKEN_CAM       0x48004f10
#define CM_CLKSEL_CAM       0x48004F40
#define CM_FCLKEN_PER       0x48005000
#define CM_ICLKEN_PER       0x48005010
#define CM_CLKSEL_PER       0x48005040
#define CM_CLKSEL1_EMU      0x48005140

#define PRM_CLKSEL           0x48306d40
#define PRM_RSTCTRL          0x48307250
#define PRM_CLKSRC_CTRL      0x48307270

/* SMX-APE */
#define PM_RT_APE_BASE_ADDR_ARM		(SMX_APE_BASE + 0x10000)
#define PM_GPMC_BASE_ADDR_ARM		(SMX_APE_BASE + 0x12400)
#define PM_OCM_RAM_BASE_ADDR_ARM	(SMX_APE_BASE + 0x12800)
#define PM_OCM_ROM_BASE_ADDR_ARM	(SMX_APE_BASE + 0x12C00)
#define PM_IVA2_BASE_ADDR_ARM		(SMX_APE_BASE + 0x14000)

#define RT_REQ_INFO_PERMISSION_1	(PM_RT_APE_BASE_ADDR_ARM + 0x68)
#define RT_READ_PERMISSION_0		(PM_RT_APE_BASE_ADDR_ARM + 0x50)
#define RT_WRITE_PERMISSION_0		(PM_RT_APE_BASE_ADDR_ARM + 0x58)
#define RT_ADDR_MATCH_1			(PM_RT_APE_BASE_ADDR_ARM + 0x60)

#define GPMC_REQ_INFO_PERMISSION_0	(PM_GPMC_BASE_ADDR_ARM + 0x48)
#define GPMC_READ_PERMISSION_0		(PM_GPMC_BASE_ADDR_ARM + 0x50)
#define GPMC_WRITE_PERMISSION_0		(PM_GPMC_BASE_ADDR_ARM + 0x58)

#define OCM_REQ_INFO_PERMISSION_0	(PM_OCM_RAM_BASE_ADDR_ARM + 0x48)
#define OCM_READ_PERMISSION_0		(PM_OCM_RAM_BASE_ADDR_ARM + 0x50)
#define OCM_WRITE_PERMISSION_0		(PM_OCM_RAM_BASE_ADDR_ARM + 0x58)
#define OCM_ADDR_MATCH_2		(PM_OCM_RAM_BASE_ADDR_ARM + 0x80)

#define IVA2_REQ_INFO_PERMISSION_0	(PM_IVA2_BASE_ADDR_ARM + 0x48)
#define IVA2_READ_PERMISSION_0		(PM_IVA2_BASE_ADDR_ARM + 0x50)
#define IVA2_WRITE_PERMISSION_0		(PM_IVA2_BASE_ADDR_ARM + 0x58)

#define IVA2_REQ_INFO_PERMISSION_1	(PM_IVA2_BASE_ADDR_ARM + 0x68)
#define IVA2_READ_PERMISSION_1		(PM_IVA2_BASE_ADDR_ARM + 0x70)
#define IVA2_WRITE_PERMISSION_1		(PM_IVA2_BASE_ADDR_ARM + 0x78)

#define IVA2_REQ_INFO_PERMISSION_2	(PM_IVA2_BASE_ADDR_ARM + 0x88)
#define IVA2_READ_PERMISSION_2		(PM_IVA2_BASE_ADDR_ARM + 0x90)
#define IVA2_WRITE_PERMISSION_2		(PM_IVA2_BASE_ADDR_ARM + 0x98)

#define IVA2_REQ_INFO_PERMISSION_3	(PM_IVA2_BASE_ADDR_ARM + 0xA8)
#define IVA2_READ_PERMISSION_3		(PM_IVA2_BASE_ADDR_ARM + 0xB0)
#define IVA2_WRITE_PERMISSION_3		(PM_IVA2_BASE_ADDR_ARM + 0xB8)

/* I2C base */
#define I2C_BASE1		(OMAP34XX_CORE_L4_IO_BASE + 0x70000)
#define I2C_BASE2		(OMAP34XX_CORE_L4_IO_BASE + 0x72000)
#define I2C_BASE3		(OMAP34XX_CORE_L4_IO_BASE + 0x60000)

#endif

