#ifndef __I2C_H__
#define __I2C_H__

///
/// \file
/// Functions for accessing the I2C bus, used internally by the audio
/// library.
///

#include <stdint.h>

///
/// Initialize the I2C hardware.
///
/// \param speed The bus speed to use (100000 or 400000?).
/// \param slaveaddr The slave address (1?).
///
/// \remarks Code copied from elsewhere and not entirely understood.
///

void InitI2C(int speed,int slaveaddr);

/// 
/// Read a byte from a device on the I2C bus.
///
/// \param devaddr The address of the device.
/// \param regoffset The number of the register on the device to read.
///
/// \return The byte read.
///

uint8_t ReadI2CByte(uint8_t devaddr,uint8_t regoffset);

/// 
/// Read a byte from a device on the I2C bus, with error signalling.
///
/// \param devaddr The address of the device.
/// \param regoffset The number of the register on the device to read.
/// \param value A pointer to a byte where the value read will be
///              stored on return.
///
/// \return Error condition. 0 if there was no error, non-zero otherwise.
///

int GetI2CByte(uint8_t devaddr,uint8_t regoffset,uint8_t *value);

/// 
/// Write a byte to a device on the I2C bus.
///
/// \param devaddr The address of the device.
/// \param regoffset The number of the register on the device to write.
/// \param value The byte value to write.
///

int WriteI2CByte(uint8_t devaddr,uint8_t regoffset,uint8_t value);

#endif

