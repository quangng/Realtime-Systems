#ifndef __AUDIO_H__
#define __AUDIO_H__

///
/// \file
/// Functions for using the BeagleBoard audio hardware. There are
/// functions for reading and writing samples in stereo at 44.1 kHz.
///

#include <stdint.h>
#include <stdbool.h>

///
/// Initializes the audio hardware. The hardware is configured to send
/// and receive audio data at the given frequency in 16 bit stereo.
///
/// \param frequency The sample rate to use, in Hz. Valid values are 8000,
///                  11025, 12000, 16000, 22050, 24000, 32000, 44100,
///                  48000 and 96000.
///
/// \remarks Timing: Does 24 single-byte I2C transfers. Exact bus speed
/// unknown, but slow.
///

void InitAudio(int frequency);

///
/// Check if there are any samples available to read in the receive
/// buffer.
///
/// \return True if there are at least two samples available in the
///         buffer.
///
/// \remarks Timing: Does not use external buses.
///

bool IsAudioReadyToRead();

///
/// Check if there is space to write samples to the transmit buffer.
///
/// \return True if there is space for at least two samples available
///         in the buffer.
///
/// \remarks Timing: Does not use external buses.
///

bool IsAudioReadyToWrite();

///
/// Read as many samples from the audio buffer as are available.
///
/// \param buffer A pointer to a buffer of 32-bit signed integers that
///               will contain the received samples. Samples from the
///               left and right channels will be interleaved in the
///               buffer. Values are between -32768 and 32767.
/// \param numsamples The size of the buffer in number of samples. The
///                   function will only read this many samples at most
///                   from the buffer.
///
/// \return The actual number of samples read. If there are not enough
///         samples available in the buffer, this value will be less
///         than numsamples, and the remaining places in the sample
///         buffer will be undefined.
///
/// \remarks Timing: Does not use external buses.
///

int ReadAudioBuffer(int32_t *buffer,int numsamples);

///
/// Read a given number of samples from the audio buffer, blocking if
/// enough samples are not yet available.
///
/// \param buffer A pointer to a buffer of 32-bit signed integers that
///               will contain the received samples. Samples from the
///               left and right channels will be interleaved in the
///               buffer. Values are between -32768 and 32767.
/// \param numsamples The size of the buffer in number of samples. The
///                   function will always read this many samples.
///
/// \remarks Timing: Blocks until enough samples have been received
///                  to fill the given buffer. Samples arrive at rate
///                  of two every 1/44100 seconds. Returns quickly if
///                  the requested number of samples are already
///                  available in the buffer.
///

void ReadFullAudioBuffer(int32_t *buffer,int numsamples);

///
/// Write a given number of samples to the audio output buffer,
/// blocking if there is not enough space in the buffer for all
/// samples.
///
/// \param buffer A pointer to a buffer of 32-bit signed integers that
///               contain the samples to be sent. Samples for the left
///               and right channels should be interleaved in the
///               buffer. Values are between -32768 and 32767.
/// \param numsamples The size of the buffer in number of samples. The
///                   function will always write this many samples.
///
/// \remarks Timing: Blocks if the audio output buffer does not have
///                  space for all samples, waiting for buffered
///                  samples to be transmitted. Samples are transmitted
///                  at rate of two every 1/44100 seconds. Returns
///                  quickly if the buffer has enough space for all
///                  samples.

void WriteAudioBuffer(int32_t *buffer,int numsamples);

///
/// Discard pending samples in the audio input buffer, clearing the
/// buffer.
///
/// \remarks Timing: Does not use external buses.
///

void DiscardAudioInput();

#endif

