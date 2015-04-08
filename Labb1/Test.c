///
/// \file
/// Test application. Used to confirm the hardware works.
///

#include "Interrupts.h"
#include "Audio.h"
#include "DisplayDOGM128.h"
#include "Encoders.h"
#include "Leds.h"
#include "Serial.h"
#include "Utils.h"
#include "Graphics.h"
#include "CT2.h"

#include <string.h>



static void DrawMarker(uint8_t *screen,int x0,int y0);
static void EraseMarker(uint8_t *screen,int x,int y);
static void DrawRotatedMarker(uint8_t *screen,int pos,int x0,int y0);
static void EraseRotatedMarker(uint8_t *screen,int pos,int x0,int y0);

int main()
{
	InstallInterruptHandlers();
	InitLeds();
	InitAudio(44100);
	InitDisplay_DOGM128();
	InitEncoders();

	SetLeds(0);

	static uint8_t screen[1024];
	memset(screen,0,sizeof(screen));

	for(int i=0;i<65536;i+=512)
	{
		int x=(12*cos16(i))>>15;
		int y=(12*sin16(i))>>15;
		DrawPixel(screen,x+24,y+24);
		DrawPixel(screen,x+64,y+24);
		DrawPixel(screen,x+104,y+24);
	}

	DrawRotatedMarker(screen,0,24,24);
	DrawRotatedMarker(screen,0,64,24);
	DrawRotatedMarker(screen,0,104,24);

	UpdateDisplay_DOGM128(screen);

	InitCT();

	PrintSerialString("Starting Beagleboard test...\n");

	int t=0;
	int lastrot[3]={0,0,0};
	bool lastpush[3]={false,false,false};
	int lastx=0,lasty=0,lastz1=0,lastz2=0,lastr=0;

	for(;;)
	{
		static int32_t inbuf[256],outbuf[256];

		SetLeds((t>>6)&3);

		ReadFullAudioBuffer(inbuf,256);

		for(int i=0;i<128;i++)
		{
			static const uint8_t bitpattern[16]=
			{0x0f,0x0f,0x0f,0x0f,0xe,0x0e,0x0c,0x08,0x10,0x30,0x70,0x70,0xf0,0xf0,0xf0,0xf0};
			int offs1=(inbuf[2*i]+32768)>>12;
			int offs2=(inbuf[2*i+1]+32768)>>12;
			screen[i+6*128]=bitpattern[offs1];
			screen[i+7*128]=bitpattern[offs2];
		}

		int x,y,z1,z2;
		ReadTouchscreenPosition_TSC2046(&x,&y,&z1,&z2);

		if(x!=lastx||y!=lasty||z1!=lastz1||z2!=lastz2)
		{
			int r=0;
			if(z1!=0) r=y*(z2-z1)/z1;

			EraseMarker(screen,127-(lastx>>5),3);
			EraseMarker(screen,3,lasty>>6);
			EraseMarker(screen,124,lastz1>>6);
			EraseMarker(screen,121,lastz2>>6);
			EraseMarker(screen,118,lastr>>10);
			DrawMarker(screen,127-(x>>5),3);
			DrawMarker(screen,3,y>>6);
			DrawMarker(screen,124,z1>>6);
			DrawMarker(screen,121,z2>>6);
			DrawMarker(screen,118,r>>10);
			lastx=x;
			lasty=y;
			lastz1=z1;
			lastz2=z2;
			lastr=r;

			if(y*(z2-z1)<z1*15000) DrawMarker(screen,127-(x>>5),y>>6);
		}

		for(int i=0;i<3;i++)
		{
			int rot=ReadEncoder(i);
			if(rot!=lastrot[i])
			{
				EraseRotatedMarker(screen,lastrot[i],24+i*40,24);
				DrawRotatedMarker(screen,rot,24+i*40,24);
				lastrot[i]=rot;
			}

			bool push=IsEncoderPushed(i);
			if(push!=lastpush[i])
			{
				if(push) DrawMarker(screen,24+i*40,24);
				else EraseMarker(screen,24+i*40,24);
				lastpush[i]=push;
			}
		}

		StartDisplayRowUpdate_DOGM128(t%8,0);
		SendDisplayRowData_DOGM128(&screen[(t%8)*128],128);
		EndDisplayRowUpdate_DOGM128();

		if(lastpush[2])
		{
			for(int i=0;i<256;i++) outbuf[i]=inbuf[i];
		}
		else
		{
			for(int i=0;i<128;i++)
			{
				int16_t samp=GetCTSample();
				outbuf[2*i]=samp;
				outbuf[2*i+1]=samp;
			}
		}

		WriteAudioBuffer(outbuf,256);

		t++;
	}
}


static void DrawMarker(uint8_t *screen,int x,int y)
{
	DrawPixel(screen,x,y);
	DrawPixel(screen,x+1,y);
	DrawPixel(screen,x-1,y);
	DrawPixel(screen,x,y+1);
	DrawPixel(screen,x,y-1);
}

static void EraseMarker(uint8_t *screen,int x,int y)
{
	ErasePixel(screen,x,y);
	ErasePixel(screen,x+1,y);
	ErasePixel(screen,x-1,y);
	ErasePixel(screen,x,y+1);
	ErasePixel(screen,x,y-1);
}

static void DrawRotatedMarker(uint8_t *screen,int pos,int x0,int y0)
{
	int x=((9*-sin16((pos<<16)/24))>>15)+x0;
	int y=((9*cos16((pos<<16)/24))>>15)+y0;
	DrawMarker(screen,x,y);
}

static void EraseRotatedMarker(uint8_t *screen,int pos,int x0,int y0)
{
	int x=((9*-sin16((pos<<16)/24))>>15)+x0;
	int y=((9*cos16((pos<<16)/24))>>15)+y0;
	EraseMarker(screen,x,y);
}

