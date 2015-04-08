#include "Phaser.h"

#include <stdio.h>

void InitDelayPhaser(DelayPhaser *phaser,int delay,int mix,int feedback)
{
	phaser->delay=delay;
	phaser->mix=mix;
	phaser->feedback=feedback;
	phaser->k=0;
}

void SetDelayPhaserOffset(DelayPhaser *phaser,int delay)
{
	phaser->delay=delay;
}

void SetDelayPhaserMix(DelayPhaser *phaser,int mix)
{
	phaser->mix=mix;
}

void SetDelayPhaserFeedback(DelayPhaser *phaser,int feedback)
{
	phaser->feedback=feedback;
}

// Phaser implemented as a delay using a circular buffer
void RunDelayPhaser(DelayPhaser *phaser,int32_t *in,int32_t *out,int numsamples)
{
	for(int n=0;n<numsamples;n++)
	{
		phaser->k++;

		int32_t insignal=in[n];
		int32_t delayedsignal=phaser->delayBuffer[(phaser->k-phaser->delay)&(SAMPLENUMBER-1)];

		// Mix the delayed and the input signal using
		// the fixed-point mixing factor.
		int32_t outsignal=(
			(0x10000/*-phaser->mix*/)*insignal + (phaser->mix)*delayedsignal
		)>>16;

		// Mix the delayed and the input signal using
		// the fixed-point feedback factor.
		int32_t feedbacksignal=(
			(0x10000/*-phaser->feedback*/)*insignal + (phaser->feedback)*delayedsignal
		)>>16;

		out[n]=outsignal;
		phaser->delayBuffer[phaser->k&(SAMPLENUMBER-1)]=feedbacksignal;
	}
}

