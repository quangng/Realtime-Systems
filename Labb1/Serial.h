#ifndef __SERIAL_H__
#define __SERIAL_H__

///
/// \file
/// Functions for reading from and writing to the serial port, mostly
/// for debugging.
///

#include <stdint.h>
#include <stdbool.h>

/// 
/// Check if there are any bytes available in the serial port input
/// buffer.
///
/// \return True if there are bytes ready to be received with
///         ReceiveSerialByte(), false otherwise.
///
/// \remarks Timing: Does not use external buses.
///

bool AreSerialBytesAvailable();

/// 
/// Check if there is any space left in the serial port output buffer.
///
/// \return True is there is space left in the buffer so that
///         SendSerialByte() will return immediately if called, false
///         otherwise.
///
/// \remarks Timing: does not use external buses.
///

bool IsSerialBufferFull();

///
/// Send a single byte over the serial port. Blocks if the serial port
/// output buffer is full.
/// 
/// \param byte The byte to send.
///
/// \remarks Timing: If there is space in the output buffer, the
///           the function returns immediately. Otherwise, it blocks
///           until one byte has finished sending. The maximum time it
///           can take for a byte to send is 10/115200 seconds, or
///           87 us.
///

void SendSerialByte(uint8_t byte);

///
/// Receive a single byte over the serial port. Blocks if no bytes are
/// available in the serial port input buffer.
///
/// \return The byte received.
/// 
/// \remarks Timing: If there are bytes already received in the serial
///                   port input buffer, the function returns
///                   immediately. Otherwise, it blocks until a byte is
///                   received. Receiving a full byte takes 10/115200
///                   seconds, or 87 us, but if no bytes are sent over
///                   the serial connection, this function will block
///                   indefinitely. Use AreSerialBytesAvailable() to
///                   poll the port and avoid blocking if necessary.
///

uint8_t ReceiveSerialByte();

///
/// Send a string over the serial port.
///
/// \param string The null-terminated string to send.
///
/// \remarks Timing: If the string fits into the available space in the
///          serial port output buffer, this function returns
///          immediately. Otherwise, it block until enough data has
///          been sent that the remaining part of the string fits into
///          the buffer. This will at worst take (length*10)/115200
///          seconds, or about length*87 us.
///

void PrintSerialString(const char *string);

///
/// Send a byte over the serial port as a two-digit hexadecimal value.
/// The output will look like "4f" or "03". Useful mostly for simple
/// debugging.
///
/// \param byte The byte to send.
///
/// \remarks Timing: If the output fits into the available space in the
///          serial port output buffer, this function returns
///          immediately. Otherwise, it block until enough data has
///          been sent that the remaining part of the output fits into
///          the buffer. This will at worst take (2*10)/115200 seconds,
///          or about 174 us.
///

void PrintSerialHexByte(uint8_t byte);

///
/// Send a 32-bit word over the serial port as an eight-digit
/// hexadecimal value. The output will look like "12ab34cd" or
/// "00000003". Useful mostly for simple debugging.
///
/// \param word The word to send.
///
/// \remarks Timing: If the output fits into the available space in the
///          serial port output buffer, this function returns
///          immediately. Otherwise, it block until enough data has
///          been sent that the remaining part of the output fits into
///          the buffer. This will at worst take (8*10)/115200 seconds,
///          or about 694 us.
///

void PrintSerialHexWord(uint32_t word);

char Hex(int val);

#endif

