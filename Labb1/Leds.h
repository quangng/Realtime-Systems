#ifndef __LEDS_H__
#define __LEDS_H__

///
/// \file
/// Functions for controlling the LEDs on the Beagle Board, for debug
/// use.
///

#include <stdint.h>

///
/// Initializes the GPIO pins that control the BeagleBoard status LEDs.
/// Call this before using SetLeds().
///

void InitLeds();

///
/// Sets the state of the BeagleBoard status LEDs. Useful mostly for
/// simple debugging.
///
/// \param state The state of the LEDs. The first bit defines the state
///              for one LED, and the second bit the other. 0 makes
///              both LEDs turn off, 1 and 2 turns on one or the other
///              LED, and 3 turns on both.
///

void SetLeds(int state);

#endif

