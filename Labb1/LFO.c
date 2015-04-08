#include "LFO.h"

void InitLFO(LFO *lfo,int period,int amplitude)
{
	lfo->period=period;
	lfo->amplitude=amplitude;
	lfo->time=0;
}

int RunTriangleLFO(LFO *lfo)
{
	int t=lfo->time%lfo->period;

	int value=(t*lfo->amplitude*4)/lfo->period;

	// Handle fourth quadrant
	if(t>=(3*lfo->period)/4) value-=lfo->amplitude*4;
	// Handle second and third quadrants
	else if(t>=lfo->period/4) value=lfo->amplitude*2-value;

	lfo->time++;

	return value;
}

// Should be easy to add a RunSineLFO() if needed.
