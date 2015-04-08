#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>

///
/// \file
/// Helper macros for defining register names. Used internally by the
/// various libraries that access the hardware.
///

#define REG(addr) (*((volatile uint32_t *)(addr)))
#define REGARRAY32(addr) ((volatile uint32_t *)(addr))

#endif

