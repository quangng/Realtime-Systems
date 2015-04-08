#ifndef _CT2_H_
#define _CT2_H_

#include <stdint.h>

void InitCT();
int16_t GetCTSample();

int16_t sin16(uint16_t phase);
static inline int16_t cos16(uint16_t phase) { return sin16(phase+16384); }

#endif

