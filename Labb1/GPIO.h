#ifndef __GPIO_H__
#define __GPIO_H__

///
/// \file
/// Macros and functions for accessing the GPIO hardware registers in
/// the OMAP3 processor, used internally by the encoder library. GPIO
/// is programmed through direct register access, see the OMAP3 data
/// sheet for further details.
///

#include "Registers.h"

#define GPIO1_SYSCONFIG REG(0x48310010)
#define GPIO1_SYSSTATUS REG(0x48310014)
#define GPIO1_IRQSTATUS1 REG(0x48310018)
#define GPIO1_IRQENABLE1 REG(0x4831001c)
#define GPIO1_WAKEUPENABLE REG(0x48310020)
#define GPIO1_IRQSTATUS2 REG(0x48310028)
#define GPIO1_IRQENABLE2 REG(0x4831002c)
#define GPIO1_CTRL REG(0x48310030)
#define GPIO1_OE REG(0x48310034)
#define GPIO1_DATAIN REG(0x48310038)
#define GPIO1_DATAOUT REG(0x4831003c)
#define GPIO1_LEVELDETECT0 REG(0x48310040)
#define GPIO1_LEVELDETECT1 REG(0x48310044)
#define GPIO1_RISINGDETECT REG(0x48310048)
#define GPIO1_FALLINGDETECT REG(0x4831004c)
#define GPIO1_DEBOUNCENABLE REG(0x48310050)
#define GPIO1_DEBOUNCINGTIME REG(0x48310054)
#define GPIO1_CLEARIRQENABLE1 REG(0x48310060)
#define GPIO1_SETIRQENABLE1 REG(0x48310064)
#define GPIO1_CLEARIRQENABLE2 REG(0x48310070)
#define GPIO1_SETIRQENABLE2 REG(0x48310074)
#define GPIO1_CLEARWKUENA REG(0x48310080)
#define GPIO1_SETWKUENA REG(0x48310084)
#define GPIO1_CLEARDATAOUT REG(0x48310090)
#define GPIO1_SETDATAOUT REG(0x48310094)

#define GPIO2_SYSCONFIG REG(0x49050010)
#define GPIO2_SYSSTATUS REG(0x49050014)
#define GPIO2_IRQSTATUS1 REG(0x49050018)
#define GPIO2_IRQENABLE1 REG(0x4905001c)
#define GPIO2_WAKEUPENABLE REG(0x49050020)
#define GPIO2_IRQSTATUS2 REG(0x49050028)
#define GPIO2_IRQENABLE2 REG(0x4905002c)
#define GPIO2_CTRL REG(0x49050030)
#define GPIO2_OE REG(0x49050034)
#define GPIO2_DATAIN REG(0x49050038)
#define GPIO2_DATAOUT REG(0x4905003c)
#define GPIO2_LEVELDETECT0 REG(0x49050040)
#define GPIO2_LEVELDETECT1 REG(0x49050044)
#define GPIO2_RISINGDETECT REG(0x49050048)
#define GPIO2_FALLINGDETECT REG(0x4905004c)
#define GPIO2_DEBOUNCENABLE REG(0x49050050)
#define GPIO2_DEBOUNCINGTIME REG(0x49050054)
#define GPIO2_CLEARIRQENABLE1 REG(0x49050060)
#define GPIO2_SETIRQENABLE1 REG(0x49050064)
#define GPIO2_CLEARIRQENABLE2 REG(0x49050070)
#define GPIO2_SETIRQENABLE2 REG(0x49050074)
#define GPIO2_CLEARWKUENA REG(0x49050080)
#define GPIO2_SETWKUENA REG(0x49050084)
#define GPIO2_CLEARDATAOUT REG(0x49050090)
#define GPIO2_SETDATAOUT REG(0x49050094)

#define GPIO3_SYSCONFIG REG(0x49052010)
#define GPIO3_SYSSTATUS REG(0x49052014)
#define GPIO3_IRQSTATUS1 REG(0x49052018)
#define GPIO3_IRQENABLE1 REG(0x4905201c)
#define GPIO3_WAKEUPENABLE REG(0x49052020)
#define GPIO3_IRQSTATUS2 REG(0x49052028)
#define GPIO3_IRQENABLE2 REG(0x4905202c)
#define GPIO3_CTRL REG(0x49052030)
#define GPIO3_OE REG(0x49052034)
#define GPIO3_DATAIN REG(0x49052038)
#define GPIO3_DATAOUT REG(0x4905203c)
#define GPIO3_LEVELDETECT0 REG(0x49052040)
#define GPIO3_LEVELDETECT1 REG(0x49052044)
#define GPIO3_RISINGDETECT REG(0x49052048)
#define GPIO3_FALLINGDETECT REG(0x4905204c)
#define GPIO3_DEBOUNCENABLE REG(0x49052050)
#define GPIO3_DEBOUNCINGTIME REG(0x49052054)
#define GPIO3_CLEARIRQENABLE1 REG(0x49052060)
#define GPIO3_SETIRQENABLE1 REG(0x49052064)
#define GPIO3_CLEARIRQENABLE2 REG(0x49052070)
#define GPIO3_SETIRQENABLE2 REG(0x49052074)
#define GPIO3_CLEARWKUENA REG(0x49052080)
#define GPIO3_SETWKUENA REG(0x49052084)
#define GPIO3_CLEARDATAOUT REG(0x49052090)
#define GPIO3_SETDATAOUT REG(0x49052094)

#define GPIO4_SYSCONFIG REG(0x49054010)
#define GPIO4_SYSSTATUS REG(0x49054014)
#define GPIO4_IRQSTATUS1 REG(0x49054018)
#define GPIO4_IRQENABLE1 REG(0x4905401c)
#define GPIO4_WAKEUPENABLE REG(0x49054020)
#define GPIO4_IRQSTATUS2 REG(0x49054028)
#define GPIO4_IRQENABLE2 REG(0x4905402c)
#define GPIO4_CTRL REG(0x49054030)
#define GPIO4_OE REG(0x49054034)
#define GPIO4_DATAIN REG(0x49054038)
#define GPIO4_DATAOUT REG(0x4905403c)
#define GPIO4_LEVELDETECT0 REG(0x49054040)
#define GPIO4_LEVELDETECT1 REG(0x49054044)
#define GPIO4_RISINGDETECT REG(0x49054048)
#define GPIO4_FALLINGDETECT REG(0x4905404c)
#define GPIO4_DEBOUNCENABLE REG(0x49054050)
#define GPIO4_DEBOUNCINGTIME REG(0x49054054)
#define GPIO4_CLEARIRQENABLE1 REG(0x49054060)
#define GPIO4_SETIRQENABLE1 REG(0x49054064)
#define GPIO4_CLEARIRQENABLE2 REG(0x49054070)
#define GPIO4_SETIRQENABLE2 REG(0x49054074)
#define GPIO4_CLEARWKUENA REG(0x49054080)
#define GPIO4_SETWKUENA REG(0x49054084)
#define GPIO4_CLEARDATAOUT REG(0x49054090)
#define GPIO4_SETDATAOUT REG(0x49054094)

#define GPIO5_SYSCONFIG REG(0x49056010)
#define GPIO5_SYSSTATUS REG(0x49056014)
#define GPIO5_IRQSTATUS1 REG(0x49056018)
#define GPIO5_IRQENABLE1 REG(0x4905601c)
#define GPIO5_WAKEUPENABLE REG(0x49056020)
#define GPIO5_IRQSTATUS2 REG(0x49056028)
#define GPIO5_IRQENABLE2 REG(0x4905602c)
#define GPIO5_CTRL REG(0x49056030)
#define GPIO5_OE REG(0x49056034)
#define GPIO5_DATAIN REG(0x49056038)
#define GPIO5_DATAOUT REG(0x4905603c)
#define GPIO5_LEVELDETECT0 REG(0x49056040)
#define GPIO5_LEVELDETECT1 REG(0x49056044)
#define GPIO5_RISINGDETECT REG(0x49056048)
#define GPIO5_FALLINGDETECT REG(0x4905604c)
#define GPIO5_DEBOUNCENABLE REG(0x49056050)
#define GPIO5_DEBOUNCINGTIME REG(0x49056054)
#define GPIO5_CLEARIRQENABLE1 REG(0x49056060)
#define GPIO5_SETIRQENABLE1 REG(0x49056064)
#define GPIO5_CLEARIRQENABLE2 REG(0x49056070)
#define GPIO5_SETIRQENABLE2 REG(0x49056074)
#define GPIO5_CLEARWKUENA REG(0x49056080)
#define GPIO5_SETWKUENA REG(0x49056084)
#define GPIO5_CLEARDATAOUT REG(0x49056090)
#define GPIO5_SETDATAOUT REG(0x49056094)

#define GPIO6_SYSCONFIG REG(0x49058010)
#define GPIO6_SYSSTATUS REG(0x49058014)
#define GPIO6_IRQSTATUS1 REG(0x49058018)
#define GPIO6_IRQENABLE1 REG(0x4905801c)
#define GPIO6_WAKEUPENABLE REG(0x49058020)
#define GPIO6_IRQSTATUS2 REG(0x49058028)
#define GPIO6_IRQENABLE2 REG(0x4905802c)
#define GPIO6_CTRL REG(0x49058030)
#define GPIO6_OE REG(0x49058034)
#define GPIO6_DATAIN REG(0x49058038)
#define GPIO6_DATAOUT REG(0x4905803c)
#define GPIO6_LEVELDETECT0 REG(0x49058040)
#define GPIO6_LEVELDETECT1 REG(0x49058044)
#define GPIO6_RISINGDETECT REG(0x49058048)
#define GPIO6_FALLINGDETECT REG(0x4905804c)
#define GPIO6_DEBOUNCENABLE REG(0x49058050)
#define GPIO6_DEBOUNCINGTIME REG(0x49058054)
#define GPIO6_CLEARIRQENABLE1 REG(0x49058060)
#define GPIO6_SETIRQENABLE1 REG(0x49058064)
#define GPIO6_CLEARIRQENABLE2 REG(0x49058070)
#define GPIO6_SETIRQENABLE2 REG(0x49058074)
#define GPIO6_CLEARWKUENA REG(0x49058080)
#define GPIO6_SETWKUENA REG(0x49058084)
#define GPIO6_CLEARDATAOUT REG(0x49058090)
#define GPIO6_SETDATAOUT REG(0x49058094)

#define SYSCONFIG_IDLEMODE_FORCE (0<<3)
#define SYSCONFIG_IDLEMODE_NONE (1<<3)
#define SYSCONFIG_IDLEMODE_SMART (2<<3)
#define SYSCONFIG_ENAWAKEUP (1<<2)
#define SYSCONFIG_SOFTRESET (1<<1)
#define SYSCONFIG_AUTOIDLE (1<<0)



#define PADCONF_MODE_0 (0<<0)
#define PADCONF_MODE_1 (1<<0)
#define PADCONF_MODE_2 (2<<0)
#define PADCONF_MODE_3 (3<<0)
#define PADCONF_MODE_4 (4<<0)
#define PADCONF_MODE_5 (5<<0)
#define PADCONF_MODE_6 (6<<0)
#define PADCONF_MODE_7 (7<<0)
#define PADCONF_PULLUDENABLE (1<<3)
#define PADCONF_PULLTYPESELECT (1<<4) // 0=down, 1=up
#define PADCONF_INPUTENABLE (1<<8)
#define PADCONF_OFFENABLE (1<<9)
#define PADCONF_OFFOUTENABLE (1<<10)
#define PADCONF_OFFOUTVALUE (1<<11)
#define PADCONF_OFFPULLUDENABLE (1<<12) // 0=down, 1=up
#define PADCONF_OFFPULLTYPESELECT (1<<13)
#define PADCONF_WAKEUPENABLE (1<<14)
#define PADCONF_WAKEUPEVENT (1<<15)

#define PADNUM_GPIO_130 0x158
#define PADNUM_GPIO_131 0x15a
#define PADNUM_GPIO_132 0x15c
#define PADNUM_GPIO_133 0x15e
#define PADNUM_GPIO_134 0x160
#define PADNUM_GPIO_135 0x162
#define PADNUM_GPIO_136 0x164
#define PADNUM_GPIO_137 0x166
#define PADNUM_GPIO_138 0x168
#define PADNUM_GPIO_139 0x16a
#define PADNUM_GPIO_140 0x16c
#define PADNUM_GPIO_141 0x16e
#define PADNUM_GPIO_142 0x170
#define PADNUM_GPIO_143 0x172
#define PADNUM_GPIO_144 0x174
#define PADNUM_GPIO_145 0x176
#define PADNUM_GPIO_146 0x178
#define PADNUM_GPIO_156 0x18c
#define PADNUM_GPIO_157 0x18e
#define PADNUM_GPIO_158 0x190
#define PADNUM_GPIO_159 0x192
#define PADNUM_GPIO_161 0x194
#define PADNUM_GPIO_162 0x196
#define PADNUM_GPIO_168 0x1be
#define PADNUM_GPIO_183 0x1c0

#define PADNUM_BEAGLE_EXT_3 PADNUM_GPIO_139
#define PADNUM_BEAGLE_EXT_4 PADNUM_GPIO_140
#define PADNUM_BEAGLE_EXT_4_ALT PADNUM_GPIO_144
#define PADNUM_BEAGLE_EXT_5 PADNUM_GPIO_138
#define PADNUM_BEAGLE_EXT_6 PADNUM_GPIO_142
#define PADNUM_BEAGLE_EXT_6_ALT PADNUM_GPIO_146
#define PADNUM_BEAGLE_EXT_7 PADNUM_GPIO_137
#define PADNUM_BEAGLE_EXT_8 PADNUM_GPIO_143
#define PADNUM_BEAGLE_EXT_9 PADNUM_GPIO_136
#define PADNUM_BEAGLE_EXT_10 PADNUM_GPIO_141
#define PADNUM_BEAGLE_EXT_10_ALT PADNUM_GPIO_145
#define PADNUM_BEAGLE_EXT_11 PADNUM_GPIO_135
#define PADNUM_BEAGLE_EXT_12 PADNUM_GPIO_158
#define PADNUM_BEAGLE_EXT_13 PADNUM_GPIO_134
#define PADNUM_BEAGLE_EXT_14 PADNUM_GPIO_162
#define PADNUM_BEAGLE_EXT_15 PADNUM_GPIO_133
#define PADNUM_BEAGLE_EXT_16 PADNUM_GPIO_161
#define PADNUM_BEAGLE_EXT_17 PADNUM_GPIO_132
#define PADNUM_BEAGLE_EXT_18 PADNUM_GPIO_159
#define PADNUM_BEAGLE_EXT_19 PADNUM_GPIO_131
#define PADNUM_BEAGLE_EXT_20 PADNUM_GPIO_156
#define PADNUM_BEAGLE_EXT_21 PADNUM_GPIO_130
#define PADNUM_BEAGLE_EXT_22 PADNUM_GPIO_157
#define PADNUM_BEAGLE_EXT_23 PADNUM_GPIO_183
#define PADNUM_BEAGLE_EXT_24 PADNUM_GPIO_168

#define CONTROL_PADCONF_BASE REGARRAY32(0x48002000)

///
/// Sets the multiplexer register for a given GPIO pad. Used to pick
/// modes for pads, and to enable input and pull-up and pull-down
/// resistors.
///
/// \param padnum The number of the GPIO pad, as given by the low bits
///               of its register address. As each register is shared
///               by two pads, the number for the pad that uses the
///               lower half of the register uses the base address, and
///               the pad that uses the upper half uses the address
///               plus 2. See the OMAP3 data sheet to find the actual
///               numbers.
/// \param state The configuration bits for the pad. See the OMAP3 data
///              sheet and the PADCONF macros for further information.
///

static inline void SetPadMultiplexer(int padnum,int state)
{
	if(padnum&2)
	{
		uint32_t val=CONTROL_PADCONF_BASE[padnum>>2];
		CONTROL_PADCONF_BASE[padnum>>2]=(val&0x0000ffff)|(state<<16);
	}
	else
	{
		uint32_t val=CONTROL_PADCONF_BASE[padnum>>2];
		CONTROL_PADCONF_BASE[padnum>>2]=(val&0xffff0000)|state;
	}
}

#endif

