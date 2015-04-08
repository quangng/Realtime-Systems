///
/// \file
/// Main program code. Implements a simple audio phaser that can be
/// configured using the rotary encoders and the touch screen.
///

#include "Audio.h"
#include "Interrupts.h"
#include "DisplayDOGM128.h"
#include "Encoders.h"
#include "Leds.h"
#include "Serial.h"
#include "Utils.h"
#include "Graphics.h"

#include "Phaser.h"
#include "LFO.h"

#include <string.h>

// Number of samples per loop iteration
#define NumberOfSamples 16

uint8_t screenupdated;

uint8_t j;

uint8_t my_updatedisplay(uint8_t *bytes) {
  //static uint8_t i = 0;

	{
		StartDisplayRowUpdate_DOGM128(j,0);
		SendDisplayRowData_DOGM128(&bytes[j*128],128);
		EndDisplayRowUpdate_DOGM128();
	}
	
    j++;
    if (j == 8)
        j = 0;  
    
    return j;        
}


void Phaser()
{
	// Initialize hardware
	InitAudio(44100);
	InitDisplay_DOGM128();
	InitEncoders();

	// Calibrate touch screen
	TwoPointCalibration cal;
	TwoPointCalibrate_TSC2046(&cal);

	// Prepare a cleared screen
	static uint8_t screen[1024];
	extern uint8_t background[1204];
	memcpy(screen,background,sizeof(screen));
	UpdateDisplay_DOGM128(screen);
    
	// Set up effect parameters and buffers
	const int midpoint=60; // The midpoint for the delay offset value
	int mix=0x8000; // Mixing factor for the phaser effect - set to 50%
	int feedback=0x8000; // Feedback factor for the phaser effect - set to 50%
	int count=0; // LFO control counter
	int maxcount=64; // The number of iterations to run before updating the LFO
	bool update=true; // Update flag for the screen
	static int32_t inbuf[NumberOfSamples*2],outbuf[NumberOfSamples*2]; // Input and output audio buffers
	static int32_t tmpbuf1[NumberOfSamples],tmpbuf2[NumberOfSamples]; // Temporary audio buffers

	// Initialize the phaser effects for both stereo channels
	static DelayPhaser dp[2];
	InitDelayPhaser(&dp[0],0,mix,feedback);
	InitDelayPhaser(&dp[1],0,mix,feedback);

	// Initialize an LFO to control the phaser effect
	LFO lfo;
	InitLFO(&lfo,80,20); // period of 80, amplitude of +-20

	// This loop processes 16 stereo samples at a time,
	// and thus run in 16/44100 seconds, or 363 microseconds.
	for(;;)
	{
		// Read input from the audio codec
		ReadFullAudioBuffer(inbuf,NumberOfSamples*2);

		// Get input from the touch screen
		int x,y;
		bool press=CalibratedTouchscreenPosition_TSC2046(&cal,&x,&y);

		if(press)
		{
			// Handle clicks on the delay slider
			if(x>=18-9&&x<55-9)
			{
				int oldcount=maxcount;
				maxcount=(63-y)*4;

				if(oldcount!=maxcount) update=true;
			}

			// Handle clicks on the mixing slider
			else if(x>=55-9&&x<92-9)
			{
				int oldmix=mix;

				mix=(63-y)*0x400;
				SetDelayPhaserMix(&dp[0],mix);
				SetDelayPhaserMix(&dp[1],mix);

				if(oldmix!=mix) update=true;
			}

			// Handle clicks on the feedback slider
			else if(x>=92-9&&x<92+2*18)
			{
				int oldfeedback=feedback;

				feedback=(63-y)*0x400;
				SetDelayPhaserFeedback(&dp[0],feedback);
				SetDelayPhaserFeedback(&dp[1],feedback);

				if(oldfeedback!=feedback) update=true;
			}
		}

		// Read input from the encoders
		int rot0=ReadEncoderChange(0);
		int rot1=ReadEncoderChange(1);
		int rot2=ReadEncoderChange(2);

		// Handle delay encoder
		if(rot0)
		{
			maxcount+=4*rot0;
			if(maxcount<0) maxcount=0;

			update=true;
		}

		// Handle mixing encoder
		if(rot1)
		{
			mix+=0x800*rot1;
			if(mix>0x10000) mix=0x10000;
			if(mix<0) mix=0;

			SetDelayPhaserMix(&dp[0],mix);
			SetDelayPhaserMix(&dp[1],mix);

			update=true;
		}

		// Handle feedback encoder
		if(rot2)
		{
			feedback+=0x800*rot2;
			if(feedback>0x10000) feedback=0x10000;
			if(feedback<0) feedback=0;

			SetDelayPhaserFeedback(&dp[0],feedback);
			SetDelayPhaserFeedback(&dp[1],feedback);

			update=true;
		}

		// Update screen if necessary
		// TODO: fix this code snippet since it takes too much time to execute and therefore distorts the audio signal
		if(update)
		{
		
			// Draw delay slider
			int delayheight=maxcount/4;
			EraseFilledRectangle(screen,18,0,18,64-delayheight);
			DrawFilledRectangle(screen,18,64-delayheight,18,delayheight);
            
			// Draw mixing slider
			
			int mixheight=mix/0x400;
			EraseFilledRectangle(screen,55,0,18,64-mixheight);
			DrawFilledRectangle(screen,55,64-mixheight,18,mixheight);
            
			// Draw feedback slider
			
			int feedbackheight=feedback/0x400;
			EraseFilledRectangle(screen,92,0,18,64-feedbackheight);
			DrawFilledRectangle(screen,92,64-feedbackheight,18,feedbackheight);
            
			//UpdateDisplay_DOGM128(screen);
			j=0;
			update=false;
			screenupdated=true;
		}

        if(screenupdated) {

	        if (my_updatedisplay(screen) == 8) {

			    screenupdated=false;
            }
        }
		// Run LFO if needed
		if(++count>=maxcount)
		{
			count=0;
			int lfoval=RunTriangleLFO(&lfo);
			SetDelayPhaserOffset(&dp[0],lfoval+midpoint);
			SetDelayPhaserOffset(&dp[1],lfoval+midpoint);
		}

		// Run phaser effect
		for(int channel=0;channel<2;channel++)
		{
			// Extract one channel from the input to a temporary buffer
			for(int i=0;i<NumberOfSamples;i++) tmpbuf1[i]=inbuf[2*i+channel];

			// Run effect in temporary buffers
			RunDelayPhaser(&dp[channel],tmpbuf1,tmpbuf2,NumberOfSamples);

			// Write processed samples back to the output buffer
			for(int i=0;i<NumberOfSamples;i++) outbuf[2*i+channel]=tmpbuf2[i];
		}

		// Send output buffer to audio codec
		WriteAudioBuffer(outbuf,NumberOfSamples*2);
	}
}

int main()
{
	InitLeds();
	InstallInterruptHandlers();
	Phaser();

	return 0;
}

