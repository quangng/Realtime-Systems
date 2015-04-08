#ifndef __UTILS_H__
#define __UTILS_H__

///
/// \file
/// Helper functions for dealing with 16.16 fixed-point numbers, some
/// integer helper functions, fixed-point sine and cosine functions,
/// and a random number generator.
///

#include <stdint.h>
#include <stdbool.h>

///
/// Random number generator.
/// 
/// \return A 32-bit random number.
///

uint32_t Random();

static inline int32_t FloatToFixed(float val) { return val*65536.0f; }
static inline int32_t IntToFixed(int val) { return val<<16; }
static inline int32_t IntToFixedPlusHalf(int val) { return (val<<16)+0x8000; }

static inline int FixedToInt(int32_t val) { return val>>16; }
static inline int FixedToRoundedInt(int32_t val) { return (val+0x8000)>>16; }

static inline int32_t FixedMul(int32_t a,int32_t b) { return ((int64_t)a*(int64_t)b)>>16; }

static inline int imin(int a,int b) { return a<b?a:b; }
static inline int imax(int a,int b) { return a>b?a:b; }
static inline int iabs(int a) { return a<0?-a:a; }
static inline int isign(int a) { return a>0?1:a<0?-1:0; }

///
/// Fixed-point sine using a lookup table.
///
/// \param a The angle. The period length is 4096. Values outside the
///          range of 0-4095 repeat as expected.
///
/// \return The sine value as a 16.16 fixed-point number.
///

int32_t isin(int a);

///
/// Fixed-point cosine using a lookup table.
///
/// \param a The angle. The period length is 4096. Values outside the
///          range of 0-4095 repeat as expected.
///
/// \return The cosine value as a 16.16 fixed-point number.
///

static inline int32_t icos(int a) { return isin(a+1024); }

#endif

