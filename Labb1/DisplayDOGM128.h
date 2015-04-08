#ifndef __DISPLAY_DOGM128_H__
#define __DISPLAY_DOGM128_H__

///
/// \file
/// Functions that interface with the LCD touchscreen on the extension
/// board. There are functions for writing bitmap data to the LCD
/// screen controller, and for reading input from the touch screen
/// controller.
///

#include <stdint.h>
#include <stdbool.h>


///
/// This function resets and initializes the LCD screen.
///
/// \remarks Timing: 14 bytes are sent over SPI at 48 MHz. The function waits until
///          all bytes have been sent before returning.
/// \remarks Theoretical: t = 14*8/24 = 4.67 us
/// \remarks Measured, per byte: 14*870 ns = 12.2 us
///

void InitDisplay_DOGM128();

/// 
/// This function updates the whole display. The display consists of 8
/// rows, each 8 pixels high. Each byte of bitmap data contains eight
/// pixels arranged vertically, and the bytes are arranged in rows from
/// top to bottom.
///
/// \param bytes A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
///
/// \remarks Timing: (3+128)*8 bytes are sent over SPI at 24 MHz. The
///          function waits until all bytes have been sent before
///          returning.
/// \remarks Theoretical: t = (3+128)*8*8/24 = 350 us
/// \remarks Measured, per byte: t = (3+128)*8*870 ns = 912 us
/// \remarks Measured, total: t = ~1000 us
///

void UpdateDisplay_DOGM128(uint8_t *bytes);

/// 
/// This function starts a (possibly partial) update of one row of the
/// display. The display consists of 8 rows, each 8 pixels high. Each
/// byte of bitmap data contains eight pixels arranged vertically.
///
/// \param row The number of the row to update, from 0 to 7.
/// \param col The number of the column to start the update at, from 0
//             to 127.
///
/// \remarks Timing: 3 bytes are sent over SPI at 24 MHz. The function
///          waits until all bytes have been sent before returning.
/// \remarks Theoretical: t = 3*8/24 = 1 us
/// \remarks Measured, per byte: t = 3*870ns = 2.6 us
///

void StartDisplayRowUpdate_DOGM128(int row,int col);

/// 
/// Send bitmap data to update a display row. Can be called multiple
/// times to send data in several batches.
/// StartDisplayRowUpdate_DOGM128() must have been called before using
/// this function.
///
/// \param bytes A pointer to the bitmap data to be sent.
/// \param num The number of bytes to send. A row consists of 128 bytes,
///            and any further bytes will be ignored.
///
/// \remarks Timing: Num bytes are sent over SPI at 24 MHz. The function
///          waits until all bytes have been sent before returning.
/// \remarks Theoretical: t = num*8/24 = num*333ns
/// \remarks Measured, per byte: t = num*870ns
///

void SendDisplayRowData_DOGM128(uint8_t *bytes,int num);

/// 
/// Finish updating a display row. Must always be called after calling
/// StartDisplayRowUpdate_DOGM128() to return the bus to the idle
/// state.
///
/// \remarks Timing: Doesn't send data.
///

void EndDisplayRowUpdate_DOGM128();

///
/// This function reads the raw values from the touch screen controller
/// ADC. The returned values represent the x and y positions of the pen
/// on the screen, and the touch pressure. These values must be
/// calibrated to be meaningful.
///
/// \param x Pointer to a variable to hold the x value on return. The
///          written value will be between 0 and 4095.
/// \param y Pointer to a variable to hold the y value on return. The
///          written value will be between 0 and 4095.
/// \param z1 Pointer to a variable to hold the first pressure value on return.
///           The written value will be between 0 and 4095.
/// \param z2 Pointer to a variable to hold the second pressure value on return.
///           The written value will be between 0 and 4095.
///
/// \remarks Timing: 9 bytes are sent over SPI at 1.5 MHz. The function
///          waits until all bytes have been sent before returning.
/// \remarks Theoretical: t = 9*8/1.5 = 48 us
///

void ReadTouchscreenPosition_TSC2046(int *x,int *y,int *z1,int *z2);

///
/// This structure contains information about the calibration of input
/// from the touch screen controller. It should not be manipulated
/// directly, but used as input for the functions
/// TwoPointCalibrate_TSC2046() and
/// CalibratedTouchscreenPosition_TSC2046() only.
///
/// \see TwoPointCalibrate_TSC2046
/// \see CalibratedTouchscreenPosition_TSC2046
///

typedef struct TwoPointCalibration
{
	int x1,x2,y1,y2;
} TwoPointCalibration;

void TwoPointCalibrate_TSC2046(TwoPointCalibration *c);
bool CalibratedTouchscreenPosition_TSC2046(TwoPointCalibration *c,int *xptr,int *yptr);

#endif

