#include "Audio.h"
#include "I2C.h"

#define REG(addr) (*((volatile uint32_t *)(addr)))
#define SREG(addr) (*((volatile int32_t *)(addr)))

#define MCBSP2_DRR_REG SREG(0x49022000)
#define MCBSP2_DXR_REG SREG(0x49022008)
#define MCBSP2_SPCR2_REG REG(0x49022010)
#define MCBSP2_SPCR1_REG REG(0x49022014)
#define MCBSP2_RCR2_REG REG(0x49022018)
#define MCBSP2_RCR1_REG REG(0x4902201C)
#define MCBSP2_XCR2_REG REG(0x49022020)
#define MCBSP2_XCR1_REG REG(0x49022024)
#define MCBSP2_SRGR2_REG REG(0x49022028)
#define MCBSP2_SRGR1_REG REG(0x4902202C)
#define MCBSP2_MCR2_REG REG(0x49022030)
#define MCBSP2_MCR1_REG REG(0x49022034)
#define MCBSP2_RCERA_REG REG(0x49022038)
#define MCBSP2_RCERB_REG REG(0x4902203C)
#define MCBSP2_XCERA_REG REG(0x49022040)
#define MCBSP2_XCERB_REG REG(0x49022044)
#define MCBSP2_PCR_REG REG(0x49022048)
#define MCBSP2_RCERC_REG REG(0x4902204C)
#define MCBSP2_RCERD_REG REG(0x49022050)
#define MCBSP2_XCERC_REG REG(0x49022054)
#define MCBSP2_XCERD_REG REG(0x49022058)
#define MCBSP2_RCERE_REG REG(0x4902205C)
#define MCBSP2_RCERF_REG REG(0x49022060)
#define MCBSP2_XCERE_REG REG(0x49022064)
#define MCBSP2_XCERF_REG REG(0x49022068)
#define MCBSP2_RCERG_REG REG(0x4902206C)
#define MCBSP2_RCERH_REG REG(0x49022070)
#define MCBSP2_XCERG_REG REG(0x49022074)
#define MCBSP2_XCERH_REG REG(0x49022078)
#define MCBSP2_UNDOCUMENTED1_REG REG(0x4902207C)
#define MCBSP2_RINTCLR_REG REG(0x49022080)
#define MCBSP2_XINTCLR_REG REG(0x49022084)
#define MCBSP2_ROVFLCLR_REG REG(0x49022088)
#define MCBSP2_SYSCONFIG_REG REG(0x4902208C)
#define MCBSP2_THRSH2_REG REG(0x49022090)
#define MCBSP2_THRSH1_REG REG(0x49022094)
#define MCBSP2_IRQSTATUS_REG REG(0x490220A0)
#define MCBSP2_IRQENABLE_REG REG(0x490220A4)
#define MCBSP2_WAKEUPEN_REG REG(0x490220A8)
#define MCBSP2_XCCR_REG REG(0x490220AC)
#define MCBSP2_RCCR_REG REG(0x490220B0)
#define MCBSP2_XBUFFSTAT_REG REG(0x490220B4)
#define MCBSP2_RBUFFSTAT_REG REG(0x490220B8)
#define MCBSP2_SSELCR_REG REG(0x490220BC)
#define MCBSP2_STATUS_REG REG(0x490220C0)


void set_leds(int state);

#define CFG_I2C_SPEED            100
#define CFG_I2C_SLAVE            1
#define CFG_I2C_BUS              0
#define CFG_I2C_BUS_SELECT       1

void InitAudio(int frequency)
{
	int mode;
	switch(frequency)
	{
		case 8000:  mode=0x00; break;
		case 11025: mode=0x10; break;
		case 12000: mode=0x20; break;
		case 16000: mode=0x40; break;
		case 22050: mode=0x50; break;
		case 24000: mode=0x60; break;
		case 32000: mode=0x80; break;
		default:
		case 44100: mode=0x90; break;
		case 48000: mode=0xa0; break;
		case 96000: mode=0xe0; break;
	}

/*	WriteI2CByte(0x4b,0x7A,0x20); // VAUX3_DEV_GRP
	WriteI2CByte(0x4b,0x7D,0x03); // VAUX3_DEDICATED
	WriteI2CByte(0x4b,0x8e,0xe0); // VPLL2_DEV_GRP
	WriteI2CByte(0x4b,0x91,0x05); // VPLL2_DEDICATED

	WriteI2CByte(0x49,0x01,0x93); // codec_MODE
	WriteI2CByte(0x49,0x02,0xc3); // OPTION
	WriteI2CByte(0x49,0x03,0x00); // ?
	WriteI2CByte(0x49,0x04,0x00); // MICBIAS_CTL
	WriteI2CByte(0x49,0x05,0x00); // ANAMICL
	WriteI2CByte(0x49,0x06,0x00); // ANAMICR
	WriteI2CByte(0x49,0x07,0x00); // AVADC_CTL
	WriteI2CByte(0x49,0x08,0x00); // ADCMICSEL
	WriteI2CByte(0x49,0x09,0x00); // DIGMIXING
	WriteI2CByte(0x49,0x0a,0x00); // ATXL1PGA
	WriteI2CByte(0x49,0x0b,0x00); // ATXR1PGA
	WriteI2CByte(0x49,0x0c,0x00); // AVTXL2PGA
	WriteI2CByte(0x49,0x0d,0x00); // AVTXR2PGA
	WriteI2CByte(0x49,0x0e,0x01); // AUDIO_IF
	WriteI2CByte(0x49,0x0f,0x00); // VOICE_IF
	WriteI2CByte(0x49,0x10,0x00); // ARXR1PGA
	WriteI2CByte(0x49,0x11,0x00); // ARXL1PGA
	WriteI2CByte(0x49,0x12,0x6c); // ARXR2PGA
	WriteI2CByte(0x49,0x13,0x6c); // ARXL2PGA
	WriteI2CByte(0x49,0x14,0x00); // VRXPGA
	WriteI2CByte(0x49,0x15,0x00); // VSTPGA
	WriteI2CByte(0x49,0x16,0x00); // VRX2ARXPGA
	WriteI2CByte(0x49,0x17,0x0c); // AVDAC_CTL
	WriteI2CByte(0x49,0x18,0x00); // 
	WriteI2CByte(0x49,0x19,0x00); // 
	WriteI2CByte(0x49,0x1a,0x00); // 
	WriteI2CByte(0x49,0x1b,0x2b); // ARXL2_APGA_CTL
	WriteI2CByte(0x49,0x1c,0x2b); // ARXR2_APGA_CTL
	WriteI2CByte(0x49,0x1d,0x00); // 
	WriteI2CByte(0x49,0x1e,0x00); // 
	WriteI2CByte(0x49,0x1f,0x00); // 
	WriteI2CByte(0x49,0x20,0x00); // 
	WriteI2CByte(0x49,0x21,0x00); // 
	WriteI2CByte(0x49,0x22,0x24); // HS_SEL
	WriteI2CByte(0x49,0x23,0x0a); // HS_GAIN_SET
	WriteI2CByte(0x49,0x24,0x42); // HS_POPN_SET
	WriteI2CByte(0x49,0x25,0x00); // 
	WriteI2CByte(0x49,0x26,0x00); // 
	WriteI2CByte(0x49,0x27,0x00); // 
	WriteI2CByte(0x49,0x28,0x00); // 
	WriteI2CByte(0x49,0x29,0x00); // 
	WriteI2CByte(0x49,0x2a,0x00); // 
	WriteI2CByte(0x49,0x2b,0x00); // 
	WriteI2CByte(0x49,0x2c,0x00); // 
	WriteI2CByte(0x49,0x2d,0x00); // 
	WriteI2CByte(0x49,0x2e,0x00); // 
	WriteI2CByte(0x49,0x2f,0x00); // 
	WriteI2CByte(0x49,0x30,0x00); // 
	WriteI2CByte(0x49,0x31,0x00); // 
	WriteI2CByte(0x49,0x32,0x00); // 
	WriteI2CByte(0x49,0x33,0x00); // 
	WriteI2CByte(0x49,0x34,0x00); // 
	WriteI2CByte(0x49,0x35,0x00); // 
	WriteI2CByte(0x49,0x36,0x00); // 
	WriteI2CByte(0x49,0x37,0x00); // 
	WriteI2CByte(0x49,0x38,0x00); // 
	WriteI2CByte(0x49,0x39,0x00); // 
	WriteI2CByte(0x49,0x3a,0x15); // APLL_CTL
	WriteI2CByte(0x49,0x3b,0x00); // 
	WriteI2CByte(0x49,0x3c,0x00); // 
	WriteI2CByte(0x49,0x3d,0x00); // 
	WriteI2CByte(0x49,0x3e,0x00); // 
	WriteI2CByte(0x49,0x3f,0x00); // 
	WriteI2CByte(0x49,0x40,0x00); // 
	WriteI2CByte(0x49,0x41,0x00); // 
	WriteI2CByte(0x49,0x42,0x00); // 
	WriteI2CByte(0x49,0x43,0x00); // 
	WriteI2CByte(0x49,0x44,0x00); // 
	WriteI2CByte(0x49,0x45,0x00); // 
	WriteI2CByte(0x49,0x46,0x00); // 
	WriteI2CByte(0x49,0x47,0x00); // 
	WriteI2CByte(0x49,0x48,0x00); // 
	WriteI2CByte(0x49,0x49,0x00); // 
*/

	WriteI2CByte(0x4b,0x44,0xc0); // PROTECT_KEY
	WriteI2CByte(0x4b,0x44,0x0c); // PROTECT_KEY
	WriteI2CByte(0x4b,0x3b,0x1a); // CFG_BOOT
	WriteI2CByte(0x4b,0x44,0x00); // PROTECT_KEY

	WriteI2CByte(0x49,0x02,0xc3); // OPTION
//	WriteI2CByte(0x49,0x04,0x04); // MICBIAS_CTL
	WriteI2CByte(0x49,0x05,0x14); // ANAMICL
	WriteI2CByte(0x49,0x06,0x14); // ANAMICR
	WriteI2CByte(0x49,0x07,0x0a); // AVADC_CTL
	WriteI2CByte(0x49,0x0a,0x00); // ATXL1PGA
	WriteI2CByte(0x49,0x0b,0x00); // ATXR1PGA
	WriteI2CByte(0x49,0x0e,0x01); // AUDIO_IF - 16 bit word length, 16 bit data, codec mode
	WriteI2CByte(0x49,0x48,0x00); // ANAMIC_GAIN

	WriteI2CByte(0x49,0x12,0x3f); // ARXR2PGA
	WriteI2CByte(0x49,0x13,0x3f); // ARXL2PGA
	WriteI2CByte(0x49,0x17,0x0c); // AVDAC_CTL

	WriteI2CByte(0x49,0x1b,0x33); // ARXL2_APGA_CTL
	WriteI2CByte(0x49,0x1c,0x33); // ARXR2_APGA_CTL
//	WriteI2CByte(0x49,0x1b,0x2d); // ARXL2_APGA_CTL
//	WriteI2CByte(0x49,0x1c,0x2d); // ARXR2_APGA_CTL
//	WriteI2CByte(0x49,0x3e,0x20); // MISC_SET_1

	WriteI2CByte(0x49,0x22,0x24); // HS_SEL
	WriteI2CByte(0x49,0x23,0x0a); // HS_GAIN_SET
//	WriteI2CByte(0x49,0x24,0x42); // HS_POPN_SET

	WriteI2CByte(0x49,0x3a,0x16); // APLL_CTL - set PLL input frequency to 26 MHz (?)

	WriteI2CByte(0x49,0x01,mode|0x03); // codec_MODE

	WriteI2CByte(0x49,0x24,0x00|0x14); // HS_POPN_SET
	WriteI2CByte(0x49,0x24,0x00|0x14|0x40); // HS_POPN_SET
	WriteI2CByte(0x49,0x24,0x00|0x14|0x40|0x02); // HS_POPN_SET

	WriteI2CByte(0x49,0x01,mode|0x01); // codec_MODE
	WriteI2CByte(0x49,0x01,mode|0x03); // codec_MODE

	MCBSP2_SPCR2_REG=0x00000200; // place transmitter in reset
	MCBSP2_SPCR1_REG=0x00002000; // place receiver in reset, sign-extend input values

	MCBSP2_SYSCONFIG_REG=0x00000208;
//MCBSP2_MCR2_REG=0;
//MCBSP2_MCR1_REG=0;
	MCBSP2_THRSH2_REG=0x0000002; // Always read and write samples in chunks of at least 2
	MCBSP2_THRSH1_REG=0x0000002;
	MCBSP2_XCCR_REG=0x00001008;
	MCBSP2_RCCR_REG=0x00000808;
	MCBSP2_RCR2_REG=0x00008041; // dual phase, 16 bit data, 1 bit delay
	MCBSP2_RCR1_REG=0x00000040; // 16 bit data in second phase
	MCBSP2_XCR2_REG=0x00008041; // dual phase, 16 bit data, 1 bit delay
	MCBSP2_XCR1_REG=0x00000040; // 16 bit data in second phase
	MCBSP2_SRGR2_REG=0x00004000; // use falling edge of clock and frame sync
	MCBSP2_SRGR1_REG=0x00000000;
	MCBSP2_PCR_REG=0x00000083; // 81?
	MCBSP2_UNDOCUMENTED1_REG=0x00000023;
//	MCBSP2_DXR_REG=0x000056f3;

	MCBSP2_SPCR2_REG=0x00000201; // take transmitter out of reset
	MCBSP2_SPCR1_REG=0x00002001; // take receiver out of reset, sign-extend input values
}

bool IsAudioReadyToRead()
{
	return (MCBSP2_SPCR1_REG&0x02)?true:false;
}

bool IsAudioReadyToWrite()
{
	return (MCBSP2_SPCR2_REG&0x02)?true:false;
//	return MCBSP2_XBUFFSTAT_REG>=2;
}

int ReadAudioBuffer(int32_t *buffer,int numsamples)
{
	int num=0;

	while(num<numsamples && IsAudioReadyToRead())
	{
		buffer[num++]=MCBSP2_DRR_REG;
	}

	return num;
}

void ReadFullAudioBuffer(int32_t *buffer,int numsamples)
{
	for(int i=0;i<numsamples;i++)
	{
		while(!IsAudioReadyToRead());
		buffer[i]=MCBSP2_DRR_REG;
 	}
}

void WriteAudioBuffer(int32_t *buffer,int numsamples)
{
	for(int i=0;i<numsamples;i++)
	{
		while(!IsAudioReadyToWrite());
		MCBSP2_DXR_REG=buffer[i];
	}
}

void DiscardAudioInput()
{
	while(IsAudioReadyToRead()) MCBSP2_DRR_REG;
}

