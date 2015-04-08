#ifndef __ENCODERS_H__
#define __ENCODERS_H__

///
/// \file
/// Functions for reading input from the rotary encoder knobs on the
/// extension board. The input from these knobs are handled by an
/// interrupt, which triggers on changes in position and updates
/// internal position variables, which can be read by the main program
/// through the functions provided by this library.
///

#include <stdint.h>
#include <stdbool.h>

///
/// Configure hardware for reading the encoders. Calling this function
/// also sets up the interrupt handler, and initializes all positions
/// to 0. Note that InstallInterruptHandlers() also needs to be called
/// for the interrupts to work.
///
/// \remarks Timing: Does not use external buses.
///

void InitEncoders();

///
/// Read the position of an encoder.
///
/// \param n The number of the encoder to read, from 0 to 2.
///
/// \return The current position of the encoder. There are 24 steps in
///         one full turn of the encoder knob.
///
/// \remarks Timing: Does not use external buses.
///

int ReadEncoder(int n);

///
/// Read the change in the encoder position since the previous call.
///
/// \param n The number of the encoder to read, from 0 to 2.
///
/// \return The difference in the position of the encoder since the
///         last time this function was called for this encoder.
///         Positive changes mean a clockwise turn, negative changes
///         a counter-clockwise turn.
///
/// \remarks Timing: Does not use external buses.
///

int ReadEncoderChange(int n);

///
/// Description: Check if an encoder knob has been pushed down.
///
/// \param n The number of the encoder to check, from 0 to 2.
///
/// \return True if the knob is being pushed down, false otherwise.
///
/// \remarks Timing: Does not use external buses.
///

bool IsEncoderPushed(int n);

#endif

