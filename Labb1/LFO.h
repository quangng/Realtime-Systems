#ifndef __LFO_H__
#define __LFO_H__

///
/// \file
/// Implementation of a simple triangular low-frequency oscillator.
///

///
/// LFO internal data structure. For use with InitLFO() and
/// RunTriangleLFO(). Do not access directly.
///

typedef struct LFO
{
	int period,amplitude;
	int time;
} LFO;

///
/// Initialize an LFO.
///
/// \param lfo A pointer to the LFO data structure to initialize.
/// \param period The period of the LFO. The output of the LFO will
///               repeat after this many invocations.
/// \param amplitude The amplitude of the LFO. The output of the LFO
///                  will be between amplitude and -amplitude.
///

void InitLFO(LFO *lfo,int period,int amplitude);

///
/// Run an LFO to generate triangle-wave output. A triangular LFO will
/// produce output that increases linearly from 0 to the configured
/// amplitude of the LFO, then decreases linearly to the negative value
/// of the amplitude, and then increases linearly back to 0, which it
/// will reach after the number of invocations specified for the
/// period in InitLFO().
///
/// \param lfo A pointer to the LFO data structure to use.
///

int RunTriangleLFO(LFO *lfo);

#endif
