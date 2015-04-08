#ifndef _PHASER_H_
#define _PHASER_H_

///
/// \file
/// Implementation of a phaser effect using a delay.
///

#include <stdint.h>

#define SAMPLENUMBER 65536

///
/// Phaser internal data structure. For use with the delay phaser
/// functions. Do not access directly.
///

typedef struct DelayPhaser
{
	int delay;
	int32_t mix,feedback;

	int32_t delayBuffer[SAMPLENUMBER];
	int k; // global index to delayBuffer
} DelayPhaser;

///
/// Initialize a phaser effect implemented using a delay.
/// 
/// \param phaser A pointer to the phaser effect data structure.
/// \param delay The delay to apply to the audio signal, in samples.
/// \param mix The mixing factor for the direct and delayed signals.
///            The range is 0-0x10000, where 0x10000 is maximum effect
///            and 0 is no effect.
/// \param mix The feedback factor for the feeding the output back into
///            the delayed signal. The range is 0-0x10000, where
///            0x10000 is full feedback and 0 is no feedback.
///

void InitDelayPhaser(DelayPhaser *phaser,int delay,int mix,int feedback);

///
/// Set the delay of the phaser effect.
///
/// \param phaser A pointer to the phaser effect data structure.
/// \param delay The delay to apply to the audio signal, in samples.
///

void SetDelayPhaserOffset(DelayPhaser *phaser,int delay);

///
/// Set the mixing factor of the phaser effect.
///
/// \param phaser A pointer to the phaser effect data structure.
/// \param mix The mixing factor for the direct and delayed signals.
///            The range is 0-0x10000, where 0x10000 is maximum effect
///            and 0 is no effect.
///

void SetDelayPhaserMix(DelayPhaser *phaser,int mix);

///
/// Set the feedback factor of the phaser effect.
///
/// \param phaser A pointer to the phaser effect data structure.
/// \param mix The feedback factor for the feeding the output back into
///            the delayed signal. The range is 0-0x10000, where
///            0x10000 is full feedback and 0 is no feedback.
///

void SetDelayPhaserFeedback(DelayPhaser *phaser,int feedback);

///
/// Run the phaser effect. The input signal is mixed with a delayed
/// version of earlier input, and written to the output buffer.
///
/// \param phaser A pointer to the phaser effect data structure.
/// \param in The input sample buffer.
/// \param out The output sample buffer.
/// \param numsamples The number of samples to process. The in and out
///                   buffers should contain this many samples.
///

void RunDelayPhaser(DelayPhaser *phaser,int32_t *in,int32_t *out,int numsamples);

#endif
