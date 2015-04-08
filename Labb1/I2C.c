/*
 * Basic I2C functions
 *
 * Copyright (c) 2004 Texas Instruments
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Author: Jian Zhang jzhang@ti.com, Texas Instruments
 *
 * Copyright (c) 2003 Wolfgang Denk, wd@denx.de
 * Rewritten to fit into the current U-Boot framework
 *
 * Adapted for OMAP2420 I2C, r-woodruff2@ti.com
 *
 */

#include "I2C.h"

#define CONFIG_OMAP34XX

#define I2C_RXTX_LEN	128	/* maximum tx/rx buffer length */

typedef unsigned char u8;
typedef unsigned char uchar;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned int uint;

#include "CPU.h"

#define CFG_I2C_SPEED            100
#define CFG_I2C_SLAVE            1
#define CFG_I2C_BUS              0
#define CFG_I2C_BUS_SELECT       1


#define I2C_DEFAULT_BASE I2C_BASE1

#define I2C_REV                  0x00
#define I2C_IE                   0x04
#define I2C_STAT                 0x08
#define I2C_IV                   0x0c
#define I2C_BUF                  0x14
#define I2C_CNT                  0x18
#define I2C_DATA                 0x1c
#define I2C_SYSC                 0x20
#define I2C_CON                  0x24
#define I2C_OA                   0x28
#define I2C_SA                   0x2c
#define I2C_PSC                  0x30
#define I2C_SCLL                 0x34
#define I2C_SCLH                 0x38
#define I2C_SYSTEST              0x3c

/* I2C masks */

/* I2C Interrupt Enable Register (I2C_IE): */
#define I2C_IE_GC_IE    (1 << 5)
#define I2C_IE_XRDY_IE  (1 << 4)	/* Transmit data ready interrupt enable */
#define I2C_IE_RRDY_IE  (1 << 3)	/* Receive data ready interrupt enable */
#define I2C_IE_ARDY_IE  (1 << 2)	/* Register access ready interrupt enable */
#define I2C_IE_NACK_IE  (1 << 1)	/* No acknowledgment interrupt enable */
#define I2C_IE_AL_IE    (1 << 0)	/* Arbitration lost interrupt enable */

/* I2C Status Register (I2C_STAT): */

#define I2C_STAT_SBD    (1 << 15)	/* Single byte data */
#define I2C_STAT_BB     (1 << 12)	/* Bus busy */
#define I2C_STAT_ROVR   (1 << 11)	/* Receive overrun */
#define I2C_STAT_XUDF   (1 << 10)	/* Transmit underflow */
#define I2C_STAT_AAS    (1 << 9)	/* Address as slave */
#define I2C_STAT_GC     (1 << 5)
#define I2C_STAT_XRDY   (1 << 4)	/* Transmit data ready */
#define I2C_STAT_RRDY   (1 << 3)	/* Receive data ready */
#define I2C_STAT_ARDY   (1 << 2)	/* Register access ready */
#define I2C_STAT_NACK   (1 << 1)	/* No acknowledgment interrupt enable */
#define I2C_STAT_AL     (1 << 0)	/* Arbitration lost interrupt enable */

/* I2C Interrupt Code Register (I2C_INTCODE): */

#define I2C_INTCODE_MASK        7
#define I2C_INTCODE_NONE        0
#define I2C_INTCODE_AL          1	/* Arbitration lost */
#define I2C_INTCODE_NAK         2	/* No acknowledgement/general call */
#define I2C_INTCODE_ARDY        3	/* Register access ready */
#define I2C_INTCODE_RRDY        4	/* Rcv data ready */
#define I2C_INTCODE_XRDY        5	/* Xmit data ready */

/* I2C Buffer Configuration Register (I2C_BUF): */

#define I2C_BUF_RDMA_EN         (1 << 15)	/* Receive DMA channel enable */
#define I2C_BUF_XDMA_EN         (1 << 7)	/* Transmit DMA channel enable */

/* I2C Configuration Register (I2C_CON): */

#define I2C_CON_EN      (1 << 15)	/* I2C module enable */
#define I2C_CON_BE      (1 << 14)	/* Big endian mode */
#define I2C_CON_STB     (1 << 11)	/* Start byte mode (master mode only) */
#define I2C_CON_MST     (1 << 10)	/* Master/slave mode */
#define I2C_CON_TRX     (1 << 9)	/* Transmitter/receiver mode (master mode only) */
#define I2C_CON_XA      (1 << 8)	/* Expand address */
#define I2C_CON_STP     (1 << 1)	/* Stop condition (master mode only) */
#define I2C_CON_STT     (1 << 0)	/* Start condition (master mode only) */

/* I2C System Test Register (I2C_SYSTEST): */

#define I2C_SYSTEST_ST_EN       (1 << 15)	/* System test enable */
#define I2C_SYSTEST_FREE        (1 << 14)	/* Free running mode (on breakpoint) */
#define I2C_SYSTEST_TMODE_MASK  (3 << 12)	/* Test mode select */
#define I2C_SYSTEST_TMODE_SHIFT (12)	/* Test mode select */
#define I2C_SYSTEST_SCL_I       (1 << 3)	/* SCL line sense input value */
#define I2C_SYSTEST_SCL_O       (1 << 2)	/* SCL line drive output value */
#define I2C_SYSTEST_SDA_I       (1 << 1)	/* SDA line sense input value */
#define I2C_SYSTEST_SDA_O       (1 << 0)	/* SDA line drive output value */

#define I2C_SCLL_SCLL        (0)
#define I2C_SCLL_SCLL_M      (0xFF)
#define I2C_SCLL_HSSCLL      (8)
#define I2C_SCLH_HSSCLL_M    (0xFF)
#define I2C_SCLH_SCLH        (0)
#define I2C_SCLH_SCLH_M      (0xFF)
#define I2C_SCLH_HSSCLH      (8)
#define I2C_SCLH_HSSCLH_M    (0xFF)

#define OMAP_I2C_STANDARD          100
#define OMAP_I2C_FAST_MODE         400
#define OMAP_I2C_HIGH_SPEED        3400

#define SYSTEM_CLOCK_12       12000
#define SYSTEM_CLOCK_13       13000
#define SYSTEM_CLOCK_192      19200
#define SYSTEM_CLOCK_96       96000

#define I2C_IP_CLK SYSTEM_CLOCK_96
#define I2C_PSC_MAX          (0x0f)
#define I2C_PSC_MIN          (0x00)

void udelay(int delay)
{
//	for(int i=0;i<delay;i++)
//	{
		volatile int a;
		for(int i=1;i<3*delay/4;i++) a*=i;
//	}
}


static u32 i2c_base = I2C_DEFAULT_BASE;
//static u32 i2c_speed = CFG_I2C_SPEED;


#define __raw_writeb(v,a)		(*(volatile uint8_t *)(a) = (v))
#define __raw_writew(v,a)		(*(volatile uint16_t *)(a) = (v))
#define __raw_writel(v,a)		(*(volatile uint32_t *)(a) = (v))

#define __raw_readb(a)			(*(volatile uint8_t *)(a))
#define __raw_readw(a)			(*(volatile uint16_t *)(a))
#define __raw_readl(a)			(*(volatile uint32_t *)(a))

#define inb(a)		__raw_readb(i2c_base + (a))
#define outb(v,a)	__raw_writeb((v), (i2c_base + (a)))
#define inw(a)		__raw_readw(i2c_base +(a))
#define outw(v,a)	__raw_writew((v), (i2c_base + (a)))

static void wait_for_bb (void);
static u16 wait_for_pin (void);
static void flush_fifo(void);

#define I2C_NUM_IF 3

void InitI2C(int speed,int slaveadd)
{
	u16 scl;

	outw(0x2, I2C_SYSC); /* for ES2 after soft reset */
	udelay(1000);
	outw(0x0, I2C_SYSC); /* will probably self clear but */

	if (inw (I2C_CON) & I2C_CON_EN) {
		outw (0, I2C_CON);
		udelay (50000);
	}

	/* 12Mhz I2C module clock */
	outw (0, I2C_PSC);
	speed = speed/1000;		    /* 100 or 400 */
	scl = ((12000/(speed*2)) - 7);	/* use 7 when PSC = 0 */
	outw (scl, I2C_SCLL);
	outw (scl, I2C_SCLH);
	/* own address */
	outw (slaveadd, I2C_OA);
	outw (I2C_CON_EN, I2C_CON);

	/* have to enable intrrupts or OMAP i2c module doesn't work */
	outw (I2C_IE_XRDY_IE | I2C_IE_RRDY_IE | I2C_IE_ARDY_IE |
	      I2C_IE_NACK_IE | I2C_IE_AL_IE, I2C_IE);
	udelay (1000);
	flush_fifo();
	outw (0xFFFF, I2C_STAT);
	outw (0, I2C_CNT);
}

uint8_t ReadI2CByte(uint8_t devaddr,uint8_t regoffset)
{
	uint8_t byte=0;
	GetI2CByte(devaddr,regoffset,&byte);
	return byte;
}

int GetI2CByte(uint8_t devaddr,uint8_t regoffset,uint8_t *value)
{
	int i2c_error = 0;
	u16 status;

	/* wait until bus not busy */
	wait_for_bb ();

	/* one byte only */
	outw (1, I2C_CNT);
	/* set slave address */
	outw (devaddr, I2C_SA);
	/* no stop bit needed here */
	outw (I2C_CON_EN | I2C_CON_MST | I2C_CON_STT | I2C_CON_TRX, I2C_CON);

	status = wait_for_pin ();

	if (status & I2C_STAT_XRDY) {
		/* Important: have to use byte access */
		outb(regoffset, I2C_DATA);
		udelay (20000);
		if (inw (I2C_STAT) & I2C_STAT_NACK) {
			i2c_error = 1;
		}
	} else {
		i2c_error = 1;
	}

	if (!i2c_error) {
		/* free bus, otherwise we can't use a combined transction */
		outw (0, I2C_CON);
		while (inw (I2C_STAT) || (inw (I2C_CON) & I2C_CON_MST)) {
			udelay (10000);
			/* Have to clear pending interrupt to clear I2C_STAT */
			outw (0xFFFF, I2C_STAT);
		}

		wait_for_bb ();
		/* set slave address */
		outw (devaddr, I2C_SA);
		/* read one byte from slave */
		outw (1, I2C_CNT);
		/* need stop bit here */
		outw (I2C_CON_EN | I2C_CON_MST | I2C_CON_STT | I2C_CON_STP,
		      I2C_CON);

		status = wait_for_pin ();
		if (status & I2C_STAT_RRDY) {
#if defined(CONFIG_OMAP243X) || defined(CONFIG_OMAP34XX)
                        *value = inb(I2C_DATA);
#else
                        *value = inw(I2C_DATA);
#endif
			udelay (20000);
		} else {
			i2c_error = 1;
		}

		if (!i2c_error) {
			outw (I2C_CON_EN, I2C_CON);
			while (inw (I2C_STAT)
			       || (inw (I2C_CON) & I2C_CON_MST)) {
				udelay (10000);
				outw (0xFFFF, I2C_STAT);
			}
		}
	}
	flush_fifo();
	outw (0xFFFF, I2C_STAT);
	outw (0, I2C_CNT);
	return i2c_error;
}

int WriteI2CByte(uint8_t devaddr,uint8_t regoffset,uint8_t value)
{
	int i2c_error = 0;
	u16 status, stat;


	/* wait until bus not busy */
	wait_for_bb ();

	/* two bytes */
	outw (2, I2C_CNT);
	/* set slave address */
	outw (devaddr, I2C_SA);
	/* stop bit needed here */
	outw (I2C_CON_EN | I2C_CON_MST | I2C_CON_STT | I2C_CON_TRX |
	      I2C_CON_STP, I2C_CON);

	/* wait until state change */
	status = wait_for_pin ();

	if (status & I2C_STAT_XRDY) {
#if defined(CONFIG_OMAP243X) || defined(CONFIG_OMAP34XX)
                /* send out 1 byte */
                outb(regoffset, I2C_DATA);
                outw(I2C_STAT_XRDY, I2C_STAT);
                status = wait_for_pin();
                if ((status & I2C_STAT_XRDY)) {
                        /* send out next 1 byte */
                        outb(value, I2C_DATA);
                        outw(I2C_STAT_XRDY, I2C_STAT);
                } else {
                        i2c_error = 1;
                }
#else
                /* send out two bytes */
                outw ((value << 8) + regoffset, I2C_DATA);
#endif

		/* must have enough delay to allow BB bit to go low */
		udelay (50000);
		if (inw (I2C_STAT) & I2C_STAT_NACK) {
			i2c_error = 1;
		}
	} else {
		i2c_error = 1;
	}

	if (!i2c_error) {
		int eout = 200;

		outw (I2C_CON_EN, I2C_CON);
		while ((stat = inw (I2C_STAT)) || (inw (I2C_CON) & I2C_CON_MST)) {
			udelay (1000);
			/* have to read to clear intrrupt */
			outw (0xFFFF, I2C_STAT);
			if(--eout == 0) /* better leave with error than hang */
				break;
		}
	}
	flush_fifo();
	outw (0xFFFF, I2C_STAT);
	outw (0, I2C_CNT);
	return i2c_error;
}

static void flush_fifo(void)
{	u16 stat;

	/* note: if you try and read data when its not there or ready
	 * you get a bus error
	 */
	while(1){
		stat = inw(I2C_STAT);
		if(stat == I2C_STAT_RRDY){
#if defined(CONFIG_OMAP243X) || defined(CONFIG_OMAP34XX)
                        inb(I2C_DATA);
#else
                        inw(I2C_DATA);
#endif
			outw(I2C_STAT_RRDY,I2C_STAT);
			udelay(1000);
		}else
			break;
	}
}

int i2c_probe (uchar chip)
{
	int res = 1; /* default = fail */

	if (chip == inw (I2C_OA)) {
		return res;
	}

	/* wait until bus not busy */
	wait_for_bb ();

	/* try to read one byte */
	outw (1, I2C_CNT);
	/* set slave address */
	outw (chip, I2C_SA);
	/* stop bit needed here */
	outw (I2C_CON_EN | I2C_CON_MST | I2C_CON_STT | I2C_CON_STP, I2C_CON);
	/* enough delay for the NACK bit set */
	udelay (50000);

	if (!(inw (I2C_STAT) & I2C_STAT_NACK)) {
		res = 0;      /* success case */
		flush_fifo();
		outw(0xFFFF, I2C_STAT);
	} else {
		outw(0xFFFF, I2C_STAT);	 /* failue, clear sources*/
		outw (inw (I2C_CON) | I2C_CON_STP, I2C_CON); /* finish up xfer */
		udelay(20000);
		wait_for_bb ();
	}
	flush_fifo();
	outw (0, I2C_CNT); /* don't allow any more data in...we don't want it.*/
	outw(0xFFFF, I2C_STAT);
	return res;
}


static void wait_for_bb (void)
{
	int timeout = 10;
	u16 stat;

	outw(0xFFFF, I2C_STAT);	 /* clear current interruts...*/
	while ((stat = inw (I2C_STAT) & I2C_STAT_BB) && timeout--) {
		outw (stat, I2C_STAT);
		udelay (50000);
	}

	if (timeout <= 0) {
		//printf ("timed out in wait_for_bb: I2C_STAT=%x\n",
		//	inw (I2C_STAT));
	}
	outw(0xFFFF, I2C_STAT);	 /* clear delayed stuff*/
}

static u16 wait_for_pin (void)
{
	u16 status;
	int timeout = 10;

	do {
		udelay (1000);
		status = inw (I2C_STAT);
	} while (  !(status &
		   (I2C_STAT_ROVR | I2C_STAT_XUDF | I2C_STAT_XRDY |
		    I2C_STAT_RRDY | I2C_STAT_ARDY | I2C_STAT_NACK |
		    I2C_STAT_AL)) && timeout--);

	if (timeout <= 0) {
		//printf ("timed out in wait_for_pin: I2C_STAT=%x\n",
		//	inw (I2C_STAT));
			outw(0xFFFF, I2C_STAT);
}
	return status;
}


