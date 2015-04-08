#ifndef __SPI_H__
#define __SPI_H__

///
/// \file
/// Macros for accessing the SPI hardware registers in the OMAP3
/// processor, used internally by the display library. SPI is
/// programmed through direct register access, see the OMAP3 data sheet
/// for further details.
///

#include "Registers.h"

#define MCSPI3_SYSCONFIG REG(0x480b8010)
#define MCSPI3_SYSSTATUS REG(0x480b8014)
#define MCSPI3_IRQSTATUS REG(0x480b8018)
#define MCSPI3_IRQENABLE REG(0x480b801c)
#define MCSPI3_WAKEUPENABLE REG(0x480b8020)
#define MCSPI3_SYST REG(0x480b8024)
#define MCSPI3_MODULCTRL REG(0x480b8028)
#define MCSPI3_CH0CONF REG(0x480b802c)
#define MCSPI3_CH0STAT REG(0x480b8030)
#define MCSPI3_CH0CTRL REG(0x480b8034)
#define MCSPI3_TX0 REG(0x480b8038)
#define MCSPI3_RX0 REG(0x480b803c)
#define MCSPI3_CH1CONF REG(0x480b8040)
#define MCSPI3_CH1STAT REG(0x480b8044)
#define MCSPI3_CH1CTRL REG(0x480b8048)
#define MCSPI3_TX1 REG(0x480b804c)
#define MCSPI3_RX1 REG(0x480b8050)
#define MCSPI3_XFERLEVEL REG(0x480b807c)

#define MCSPI4_SYSCONFIG REG(0x480ba010)
#define MCSPI4_SYSSTATUS REG(0x480ba014)
#define MCSPI4_IRQSTATUS REG(0x480ba018)
#define MCSPI4_IRQENABLE REG(0x480ba01c)
#define MCSPI4_WAKEUPENABLE REG(0x480ba020)
#define MCSPI4_SYST REG(0x480ba024)
#define MCSPI4_MODULCTRL REG(0x480ba028)
#define MCSPI4_CH0CONF REG(0x480ba02c)
#define MCSPI4_CH0STAT REG(0x480ba030)
#define MCSPI4_CH0CTRL REG(0x480ba034)
#define MCSPI4_TX0 REG(0x480ba038)
#define MCSPI4_RX0 REG(0x480ba03c)
#define MCSPI4_XFERLEVEL REG(0x480ba07c)

#define MODULCTRL_SYSTEM_TEST (1<<3)
#define MODULCTRL_SLAVE (1<<2)
#define MODULCTRL_SINGLE (1<<0)

#define CHxCONF_CLKG (1<<29)
#define CHxCONF_FFER (1<<28)
#define CHxCONF_FFEW (1<<27)
#define CHxCONF_TCS_0_5 (0<<25)
#define CHxCONF_TCS_1_5 (1<<25)
#define CHxCONF_TCS_2_5 (2<<25)
#define CHxCONF_TCS_3_5 (3<<25)
#define CHxCONF_SBPOL (1<<24)
#define CHxCONF_SBE (1<<23)
#define CHxCONF_SPIENSLV_0 (0<<21)
#define CHxCONF_SPIENSLV_1 (1<<21)
#define CHxCONF_SPIENSLV_2 (2<<21)
#define CHxCONF_SPIENSLV_3 (3<<21)
#define CHxCONF_FORCE (1<<20)
#define CHxCONF_TURBO (1<<19)
#define CHxCONF_IS (1<<18)
#define CHxCONF_DPE1 (1<<17)
#define CHxCONF_DPE0 (1<<16)
#define CHxCONF_DMAR (1<<15)
#define CHxCONF_DMAW (1<<14)
#define CHxCONF_TRM_0 (0<<12)
#define CHxCONF_TRM_1 (1<<12)
#define CHxCONF_TRM_2 (2<<12)
#define CHxCONF_WL_4 (3<<7)
#define CHxCONF_WL_5 (4<<7)
#define CHxCONF_WL_6 (5<<7)
#define CHxCONF_WL_7 (6<<7)
#define CHxCONF_WL_8 (7<<7)
#define CHxCONF_WL_9 (8<<7)
#define CHxCONF_WL_10 (9<<7)
#define CHxCONF_WL_11 (10<<7)
#define CHxCONF_WL_12 (11<<7)
#define CHxCONF_WL_13 (12<<7)
#define CHxCONF_WL_14 (13<<7)
#define CHxCONF_WL_15 (14<<7)
#define CHxCONF_WL_16 (15<<7)
#define CHxCONF_WL_17 (16<<7)
#define CHxCONF_WL_18 (17<<7)
#define CHxCONF_WL_19 (18<<7)
#define CHxCONF_WL_20 (19<<7)
#define CHxCONF_WL_21 (20<<7)
#define CHxCONF_WL_22 (21<<7)
#define CHxCONF_WL_23 (22<<7)
#define CHxCONF_WL_24 (23<<7)
#define CHxCONF_WL_25 (24<<7)
#define CHxCONF_WL_26 (25<<7)
#define CHxCONF_WL_27 (26<<7)
#define CHxCONF_WL_28 (27<<7)
#define CHxCONF_WL_29 (28<<7)
#define CHxCONF_WL_30 (29<<7)
#define CHxCONF_WL_31 (30<<7)
#define CHxCONF_WL_32 (31<<7)
#define CHxCONF_EPOL (1<<6)
#define CHxCONF_CLKD_1 (0<<2)
#define CHxCONF_CLKD_2 (1<<2)
#define CHxCONF_CLKD_4 (2<<2)
#define CHxCONF_CLKD_8 (3<<2)
#define CHxCONF_CLKD_16 (4<<2)
#define CHxCONF_CLKD_32 (5<<2)
#define CHxCONF_CLKD_64 (6<<2)
#define CHxCONF_CLKD_128 (7<<2)
#define CHxCONF_CLKD_256 (8<<2)
#define CHxCONF_CLKD_512 (9<<2)
#define CHxCONF_CLKD_1024 (10<<2)
#define CHxCONF_CLKD_2048 (11<<2)
#define CHxCONF_CLKD_4096 (12<<2)
#define CHxCONF_POL (1<<1)
#define CHxCONF_PHA (1<<0)

#define CHxCONF_INPUT_SOMI 0
#define CHxCONF_INPUT_SIMO CHxCONF_IS
#define CHxCONF_OUPUT_BOTH 0
#define CHxCONF_OUPUT_SIMO CHxCONF_DPE0
#define CHxCONF_OUPUT_SOMI CHxCONF_DPE1
#define CHxCONF_OUPUT_NONE (CHxCONF_DPE0|CHxCONF_DPE1)
#define CHxCONF_TRANSMIT_AND_RECEIVE 0
#define CHxCONF_RECEIVE_ONLY CHxCONF_TRM_1
#define CHxCONF_TRANSMIT_ONLY CHxCONF_TRM_2
#define CHxCONF_CS_ACTIVE_HIGH 0
#define CHxCONF_CS_ACTIVE_LOW CHxCONF_EPOL
#define CHxCONF_CLK_ACTIVE_HIGH 0
#define CHxCONF_CLK_ACTIVE_LOW CHxCONF_POL
#define CHxCONF_PHASE_0 0
#define CHxCONF_PHASE_1 CHxCONF_PHA

#define CHxSTAT_RXFFF (1<<6)
#define CHxSTAT_RXFFE (1<<5)
#define CHxSTAT_TXFFF (1<<4)
#define CHxSTAT_TXFFE (1<<3)
#define CHxSTAT_EOT (1<<2)
#define CHxSTAT_TXS (1<<1)
#define CHxSTAT_RXS (1<<0)

#define CHxCTRL_EXTCLK(n) ((n)<<8)
#define CHxCTRL_ENABLE (1<<0)

#endif

