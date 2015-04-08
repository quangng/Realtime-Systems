#include "Encoders.h"
#include "GPIO.h"
#include "Interrupts.h"

#define CM_ICLKEN_PER REG(0x48005010)

#define EN_GPIO6 (1<<17)
#define EN_GPIO5 (1<<16)
#define EN_GPIO4 (1<<15)
#define EN_GPIO3 (1<<14)
#define EN_GPIO2 (1<<13)
#define EN_WDT3 (1<<12)
#define EN_UART3 (1<<11)
#define EN_GPT9 (1<<10)
#define EN_GPT8 (1<<9)
#define EN_GPT7 (1<<8)
#define EN_GPT6 (1<<7)
#define EN_GPT5 (1<<6)
#define EN_GPT4 (1<<5)
#define EN_GPT3 (1<<4)
#define EN_GPT2 (1<<3)
#define EN_MCBSP4 (1<<2)
#define EN_MCBSP3 (1<<1)
#define EN_MCBSP2 (1<<0)

static int position[3],lastposition[3];
static int fullposition[3],lastdirection[3];

static void Handler()
{
	for(int i=0;i<3;i++)
	{
		int bit0,bit1;

		switch(i)
		{
			case 0: bit0=(GPIO5_DATAIN>>5)&1; bit1=(GPIO5_DATAIN>>8)&1; break;
			case 1: bit0=((GPIO5_DATAIN>>13)&(GPIO5_DATAIN>>17))&1; bit1=(GPIO5_DATAIN>>9)&1; break;
			case 2: bit0=(GPIO5_DATAIN>>15)&1; bit1=(GPIO5_DATAIN>>10)&1; break;
		}

		int state=(bit0^(bit1^1))|(bit1<<1);

		switch((state-fullposition[i])&3)
		{
			case 0: // do nothing
				continue;

			case 1: // one tick up
				fullposition[i]++;
				lastdirection[i]=1;
			break;

			case 2: // two ticks in some direction
				fullposition[i]+=2*lastdirection[i];
			break;

			case 3: // one tick down
				fullposition[i]--;
				lastdirection[i]=-1;
			break;
		}

		if(lastdirection[i]==1) // moved up
		{
			if(fullposition[i]>position[i]*4+6) position[i]++;
		}
		else if(lastdirection[i]==-1) // moved down
		{
			if(fullposition[i]<position[i]*4+0) position[i]--;
		}
	}

	GPIO5_IRQSTATUS1=(1<<5)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<15)|(1<<17);
}

void InitEncoders()
{
	CM_ICLKEN_PER|=EN_GPIO6|EN_GPIO5;

	GPIO5_CTRL=2;

	SetPadMultiplexer(PADNUM_BEAGLE_EXT_3,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_4,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_4_ALT,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_5,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_6,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_6_ALT,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_7,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_8,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_9,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_10,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_10_ALT,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_15,PADCONF_MODE_4|PADCONF_INPUTENABLE|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT);
	GPIO5_OE|=(1<<5)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<15)|(1<<17) | (1<<11)|(1<<12)|(1<<14)|(1<<16)|(1<<18);
	GPIO5_FALLINGDETECT|=(1<<5)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<15)|(1<<17);
	GPIO5_RISINGDETECT|=(1<<5)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<15)|(1<<17);
	GPIO5_SETIRQENABLE1=(1<<5)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<15)|(1<<17);
	INTCPS_MIR_CLEAR(1)=(1<<1);

	SetIRQHandler(33,Handler);
	EnableInterrupts();

	for(int i=0;i<3;i++)
	{
		position[i]=lastposition[i]=0;
		fullposition[i]=3;
		lastdirection[i]=0;
	}
}

int ReadEncoder(int n)
{
	return position[n];
}

int ReadEncoderChange(int n)
{
	int res=position[n]-lastposition[n];
	lastposition[n]=position[n];
	return res;
}

bool IsEncoderPushed(int n)
{
	switch(n)
	{
		case 0: return ((GPIO5_DATAIN>>11)&1)?false:true;
		case 1: return ((GPIO5_DATAIN>>12)&(GPIO5_DATAIN>>16)&1)?false:true;
		case 2: return ((GPIO5_DATAIN>>14)&(GPIO5_DATAIN>>18)&1)?false:true;
		default: return false;
	}
}


