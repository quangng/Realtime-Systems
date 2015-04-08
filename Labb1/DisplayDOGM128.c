#include "DisplayDOGM128.h"
#include "SPI.h"
#include "GPIO.h"
#include "Leds.h"

#define CM_FCLKEN1_CORE REG(0x48004a00)
#define CM_ICLKEN1_CORE REG(0x48004a10)

static void SendSPIWord_3Ch0(uint32_t word)
{
	while((MCSPI3_CH0STAT&CHxSTAT_TXS)==0);
	MCSPI3_TX0=word;
}

static uint32_t ReceiveSPIWord_3Ch0()
{
	while((MCSPI3_CH0STAT&CHxSTAT_RXS)==0);
	return MCSPI3_RX0;
}

/*static void FinishSPITransmission_3Ch0()
{
	while((MCSPI3_CH0STAT&(CHxSTAT_TXS|CHxSTAT_EOT))!=(CHxSTAT_TXS|CHxSTAT_EOT));
}*/

static void SendSPIWord_3Ch1(uint32_t word)
{
	while((MCSPI3_CH1STAT&CHxSTAT_TXS)==0);
	MCSPI3_TX1=word;
}

/*static uint32_t ReceiveSPIWord_3Ch1()
{
	while((MCSPI3_CH1STAT&CHxSTAT_RXS)==0);
	return MCSPI3_RX1;
}*/

static void FinishSPITransmission_3Ch1()
{
	while((MCSPI3_CH1STAT&(CHxSTAT_TXS|CHxSTAT_EOT))!=(CHxSTAT_TXS|CHxSTAT_EOT));
}





static void ConfigureSPI_DOGM128()
{
	MCSPI3_MODULCTRL=MODULCTRL_SINGLE;

	MCSPI3_CH0CONF=CHxCONF_FFEW|CHxCONF_WL_8|CHxCONF_CLKD_2|
	CHxCONF_INPUT_SOMI|CHxCONF_OUPUT_SIMO|CHxCONF_TRANSMIT_ONLY|
	CHxCONF_CS_ACTIVE_LOW|CHxCONF_CLK_ACTIVE_LOW|CHxCONF_PHASE_1;
	MCSPI3_CH1CONF=CHxCONF_FFEW|CHxCONF_WL_8|CHxCONF_CLKD_2|
	CHxCONF_INPUT_SOMI|CHxCONF_OUPUT_SIMO|CHxCONF_TRANSMIT_ONLY|
	CHxCONF_CS_ACTIVE_LOW|CHxCONF_CLK_ACTIVE_LOW|CHxCONF_PHASE_1;

	SetPadMultiplexer(PADNUM_BEAGLE_EXT_19,PADCONF_MODE_1);	// pin 19 set to McSPI3_SIMO
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_21,PADCONF_MODE_1);	// pin 21 set to McSPI3_CLK
//	SetPadMultiplexer(PADNUM_BEAGLE_EXT_13,PADCONF_MODE_4); // pin 13 set to GPIO 134 instead of McSPI3_CS1
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_13,PADCONF_MODE_1); // pin 13 set to McSPI3_CS1
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_23,PADCONF_MODE_4); // pin 23 set to GPIO 183
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_24,PADCONF_MODE_4); // pin 23 set to GPIO 168

//	GPIO5_SETDATAOUT=(1<<6);
//	GPIO5_OE&=~(1<<6);
	GPIO6_SETDATAOUT=(1<<8)|(1<<23);
	GPIO6_OE&=~((1<<8)|(1<<23));
}

void InitDisplay_DOGM128()
{
	ConfigureSPI_DOGM128();

	//FinishSPITransmission();

	//GPIO5_DATAOUT|=(1<<6); // set CS pin high
	MCSPI3_CH1CTRL=CHxCTRL_ENABLE;
	MCSPI3_CH1CONF|=CHxCONF_FORCE;

	GPIO6_CLEARDATAOUT=(1<<23); // set AOP pin low to send commands

	GPIO6_CLEARDATAOUT=(1<<8); // set RES pin low to reset
	GPIO6_CLEARDATAOUT=(1<<8);
	GPIO6_CLEARDATAOUT=(1<<8);
	GPIO6_CLEARDATAOUT=(1<<8);
//	usleep(1);
	GPIO6_SETDATAOUT=(1<<8);
	GPIO6_SETDATAOUT=(1<<8);
	GPIO6_SETDATAOUT=(1<<8);
	GPIO6_SETDATAOUT=(1<<8);
//	usleep(1);

	GPIO5_CLEARDATAOUT=(1<<6);  // set CS pin low to start talking

	SendSPIWord_3Ch1(0x40+0); // display start line set
	SendSPIWord_3Ch1(0xa1); // ADC Select (0,1)
	SendSPIWord_3Ch1(0xc0); // Common output mode select (0,8)
	SendSPIWord_3Ch1(0xa6); // 
	SendSPIWord_3Ch1(0xa2); // LCD Bias set (2, 3)
	SendSPIWord_3Ch1(0x2f); // Power Control Circuit
	SendSPIWord_3Ch1(0xf8); // 
	SendSPIWord_3Ch1(0x00); // 
	SendSPIWord_3Ch1(0x27); // Voltage regulator internal resistor ratio set (0-7)
	SendSPIWord_3Ch1(0x81); // Electronic volume start byte
	SendSPIWord_3Ch1(0x16); // Electronic volume (00-3f)
	SendSPIWord_3Ch1(0xac); // 
	SendSPIWord_3Ch1(0x00); // 
	SendSPIWord_3Ch1(0xaf); // display on

	FinishSPITransmission_3Ch1();

	GPIO6_SETDATAOUT=(1<<23); // set AOP high low to stop sending commands

//	GPIO5_DATAOUT|=(1<<6); // set CS pin high
	MCSPI3_CH1CONF&=~CHxCONF_FORCE;
	MCSPI3_CH1CTRL=0;
}

void UpdateDisplay_DOGM128(uint8_t *bytes)
{
	for(int i=0;i<8;i++)
	{
		StartDisplayRowUpdate_DOGM128(i,0);
		SendDisplayRowData_DOGM128(&bytes[i*128],128);
		EndDisplayRowUpdate_DOGM128();
	}
}

void StartDisplayRowUpdate_DOGM128(int row,int col)
{
	ConfigureSPI_DOGM128();

//	FinishSPITransmission_3Ch1();

//	GPIO5_DATAOUT&=~(1<<6);  // set CS pin low to start talking
	MCSPI3_CH1CTRL=CHxCTRL_ENABLE;
	MCSPI3_CH1CONF|=CHxCONF_FORCE;

	GPIO6_CLEARDATAOUT=(1<<23); // set AOP pin low to send commands

	SendSPIWord_3Ch1(0xb0+row); // page address set
	SendSPIWord_3Ch1(0x10+((col>>4)&0x0f)); // column address set upper bit
	SendSPIWord_3Ch1(0x00+(col&0x0f)); // column address set lower bit

	FinishSPITransmission_3Ch1();

	GPIO6_SETDATAOUT=(1<<23); // set AOP high low to start sending data
}

void SendDisplayRowData_DOGM128(uint8_t *bytes,int num)
{
	for(int i=0;i<num;i++) SendSPIWord_3Ch1(bytes[i]);
	FinishSPITransmission_3Ch1();
}

void EndDisplayRowUpdate_DOGM128()
{
//	GPIO5_DATAOUT|=(1<<6); // set CS pin high
	MCSPI3_CH1CONF&=~CHxCONF_FORCE;
	MCSPI3_CH1CTRL=0;
}

/*
bool IsDisplayIdle_DOGM128()
{
	return (MCSPI3_CH0STAT&(CHxSTAT_TXFFE|CHxSTAT_TXS))==CHxSTAT_TXFFE;
}
*/




static void ConfigureSPI_TSC2046()
{
	CM_FCLKEN1_CORE|=1<<20;
	CM_ICLKEN1_CORE|=1<<20;

	MCSPI3_SYSCONFIG=0x308;

	MCSPI3_MODULCTRL=MODULCTRL_SINGLE;

	MCSPI3_CH0CONF=CHxCONF_FFER|CHxCONF_FFEW|CHxCONF_WL_8|CHxCONF_CLKD_32|
	CHxCONF_INPUT_SOMI|CHxCONF_OUPUT_SIMO|CHxCONF_TRANSMIT_AND_RECEIVE|
	CHxCONF_CS_ACTIVE_LOW|CHxCONF_CLK_ACTIVE_HIGH|CHxCONF_PHASE_0;
	MCSPI3_CH1CONF=CHxCONF_FFER|CHxCONF_FFEW|CHxCONF_WL_8|CHxCONF_CLKD_32|
	CHxCONF_INPUT_SOMI|CHxCONF_OUPUT_SIMO|CHxCONF_TRANSMIT_AND_RECEIVE|
	CHxCONF_CS_ACTIVE_LOW|CHxCONF_CLK_ACTIVE_HIGH|CHxCONF_PHASE_0;

	SetPadMultiplexer(PADNUM_BEAGLE_EXT_17,PADCONF_MODE_1|PADCONF_INPUTENABLE/*|PADCONF_PULLUDENABLE|PADCONF_PULLTYPESELECT*/); // pin 17 set to McSPI3_SOMI
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_19,PADCONF_MODE_1);	// pin 19 set to McSPI3_SIMO
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_21,PADCONF_MODE_1|PADCONF_INPUTENABLE);	// pin 21 set to McSPI3_CLK - input MUST BE ENABLED!
//	SetPadMultiplexer(PADNUM_BEAGLE_EXT_11,PADCONF_MODE_4); // pin 11 set to GPIO 134 instead of McSPI3_CS0
	SetPadMultiplexer(PADNUM_BEAGLE_EXT_11,PADCONF_MODE_1); // pin 11 set to McSPI3_CS0

//	GPIO5_SETDATAOUT=(1<<7);
//	GPIO5_OE&=~(1<<7);
}

void ReadTouchscreenPosition_TSC2046(int *x,int *y,int *z1,int *z2)
{
	ConfigureSPI_TSC2046();

	MCSPI3_CH0CTRL=CHxCTRL_ENABLE;
	MCSPI3_CH0CONF|=CHxCONF_FORCE;
//	GPIO5_CLEARDATAOUT=(1<<7);

//GPIO5_OE|=(1<<4);

	SendSPIWord_3Ch0(0x80|(1<<4));
	ReceiveSPIWord_3Ch0();
	SendSPIWord_3Ch0(0);
	*x=(ReceiveSPIWord_3Ch0()&0xff)<<5;
	SendSPIWord_3Ch0(0x80|(5<<4));
	*x|=(ReceiveSPIWord_3Ch0()&0xff)>>3;
	SendSPIWord_3Ch0(0);
	*y=(ReceiveSPIWord_3Ch0()&0xff)<<5;
	SendSPIWord_3Ch0(0x80|(3<<4));
	*y|=(ReceiveSPIWord_3Ch0()&0xff)>>3;
	SendSPIWord_3Ch0(0);
	*z1=(ReceiveSPIWord_3Ch0()&0xff)<<5;
	SendSPIWord_3Ch0(0x80|(4<<4));
	*z1|=(ReceiveSPIWord_3Ch0()&0xff)>>3;
	SendSPIWord_3Ch0(0);
	*z2=(ReceiveSPIWord_3Ch0()&0xff)<<5;
	SendSPIWord_3Ch0(0);
	*z2|=(ReceiveSPIWord_3Ch0()&0xff)>>3;


	MCSPI3_CH0CONF&=~CHxCONF_FORCE;
	MCSPI3_CH0CTRL=0;
//	GPIO5_SETDATAOUT=(1<<7);
}


static void DrawCrosshairs(uint8_t *pic,int row,int col)
{
	static uint8_t bytes[2][15]=
	{
		{0x80,0x80,0x80,0xe0,0x90,0x88,0x88,0xff,0x88,0x88,0x90,0xe0,0x80,0x80,0x80},
		{0x00,0x00,0x00,0x03,0x04,0x08,0x08,0x7f,0x08,0x08,0x04,0x03,0x00,0x00,0x00},
	};

	for(int i=0;i<15;i++) pic[row*128+col+i]=bytes[0][i];
	for(int i=0;i<15;i++) pic[row*128+128+col+i]=bytes[1][i];
}

static void ClearCrosshairs(uint8_t *pic,int row,int col)
{
	for(int i=0;i<15;i++) pic[row*128+col+i]=0;
	for(int i=0;i<15;i++) pic[row*128+128+col+i]=0;
}

static inline int IsPress(int x,int y,int z1,int z2)
{
	return y*(z2-z1)<z1*15000;
}

void TwoPointCalibrate_TSC2046(TwoPointCalibration *c)
{
	int x,y,z1,z2;
	static uint8_t pic[1024];

	for(int i=0;i<1024;i++) pic[i]=0;

	DrawCrosshairs(pic,0,0);
	UpdateDisplay_DOGM128(pic);
	ClearCrosshairs(pic,0,0);

	int counter=0;
	for(;;)
	{
		ReadTouchscreenPosition_TSC2046(&x,&y,&z1,&z2);
		if(IsPress(x,y,z1,z2) && x>2048 && y<2048)
		{
			counter++;
			if(counter>256) break;
		}
		else
		{
			counter=0;
		}
	}

	c->x1=x;
	c->y1=y;

	DrawCrosshairs(pic,6,112);
	UpdateDisplay_DOGM128(pic);

	counter=0;
	for(;;)
	{
		ReadTouchscreenPosition_TSC2046(&x,&y,&z1,&z2);
		if(IsPress(x,y,z1,z2) && x<2048 && y>2048)
		{
			counter++;
			if(counter>256) break;
		}
		else
		{
			counter=0;
		}
	}

	c->x2=x;
	c->y2=y;
}

bool CalibratedTouchscreenPosition_TSC2046(TwoPointCalibration *c,int *xptr,int *yptr)
{
	static int presscount=0;

	int x,y,z1,z2;
	ReadTouchscreenPosition_TSC2046(&x,&y,&z1,&z2);

	if(IsPress(x,y,z1,z2))
	{
		if(presscount<2)
		{
			presscount++;
			return false;
		}
	}
	else
	{
		presscount=0;
		return false;
	}

	int xcal=((x-c->x1)*(120-7))/(c->x2-c->x1)+7;
	if(xcal<0) *xptr=0;
	else if(xcal>127) *xptr=127;
	else *xptr=xcal;

	int ycal=((y-c->y1)*(56-7))/(c->y2-c->y1)+7;
	if(ycal<0) *yptr=0;
	else if(ycal>63) *yptr=63;
	else *yptr=ycal;

	return true;
}

