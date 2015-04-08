#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdint.h>

///
/// \file
/// Graphics rendering functions. There are function for rendering simple points, lines
/// and rectangles, as well as for clearing the screen.
///

/// 
/// Clears the entire screen to white.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// 
void ClearScreen(uint8_t *image);

/// 
/// Fills the entire screen with black.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// 
void FillImage(uint8_t *image);

/// 
/// Draws a single pixel on the screen.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the pixel.
/// \param y The Y coordinate of the pixel.
/// 
void DrawPixel(uint8_t *image,int x,int y);

/// 
/// Erases a single pixel on the screen.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the pixel.
/// \param y The Y coordinate of the pixel.
/// 
void ErasePixel(uint8_t *image,int x,int y);

/// 
/// Inverts a single pixel on the screen.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the pixel.
/// \param y The Y coordinate of the pixel.
/// 
void InvertPixel(uint8_t *image,int x,int y);

/// 
/// Draws a horizontal line starting from pixel position x,y on the left,
/// and continuing width pixels to the right.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the left end of the line.
/// \param y The Y coordinate of the left end of the line.
/// \param width The length of the line in pixels.
/// 
void DrawHorizontalLine(uint8_t *image,int x,int y,int width);

/// 
/// Erases a horizontal line starting from pixel position x,y on the left,
/// and continuing width pixels to the right.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the left end of the line.
/// \param y The Y coordinate of the left end of the line.
/// \param width The length of the line in pixels.
/// 
void EraseHorizontalLine(uint8_t *image,int x,int y,int width);

/// 
/// Invert a horizontal line starting from pixel position x,y on the left,
/// and continuing width pixels to the right.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the left end of the line.
/// \param y The Y coordinate of the left end of the line.
/// \param width The length of the line in pixels.
/// 
void InvertHorizontalLine(uint8_t *image,int x,int y,int width);

/// 
/// Draws a vertical line starting from pixel position x,y at the top,
/// and continuing height pixels down.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper end of the line.
/// \param y The Y coordinate of the upper end of the line.
/// \param height The length of the line in pixels.
/// 
void DrawVerticalLine(uint8_t *image,int x,int y,int height);

/// 
/// Erases a vertical line starting from pixel position x,y at the top,
/// and continuing height pixels down.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper end of the line.
/// \param y The Y coordinate of the upper end of the line.
/// \param height The length of the line in pixels.
/// 
void EraseVerticalLine(uint8_t *image,int x,int y,int height);

/// 
/// Invert a vertical line starting from pixel position x,y at the top,
/// and continuing height pixels down.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper end of the line.
/// \param y The Y coordinate of the upper end of the line.
/// \param height The length of the line in pixels.
/// 
void InvertVerticalLine(uint8_t *image,int x,int y,int height);

/// 
/// Draws a line starting from pixel position x1,y1 to pixel position x2,y2.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x1 The X coordinate of one end of the line.
/// \param y1 The Y coordinate of one end of the line.
/// \param x2 The X coordinate of the other end of the line.
/// \param y2 The Y coordinate of the other end of the line.
/// 
void DrawLine(uint8_t *image,int x1,int y1,int x2,int y2);

/// 
/// Erases a line starting from pixel position x1,y1 to pixel position x2,y2.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x1 The X coordinate of one end of the line.
/// \param y1 The Y coordinate of one end of the line.
/// \param x2 The X coordinate of the other end of the line.
/// \param y2 The Y coordinate of the other end of the line.
/// 
void EraseLine(uint8_t *image,int x1,int y1,int x2,int y2);

/// 
/// Inverts a line starting from pixel position x1,y1 to pixel position x2,y2.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x1 The X coordinate of one end of the line.
/// \param y1 The Y coordinate of one end of the line.
/// \param x2 The X coordinate of the other end of the line.
/// \param y2 The Y coordinate of the other end of the line.
/// 
void InverLine(uint8_t *image,int x1,int y1,int x2,int y2);

/// 
/// Draws the outline of a rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void DrawRectangle(uint8_t *image,int x,int y,int w,int h);

/// 
/// Erases the outline of a rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void EraseRectangle(uint8_t *image,int x,int y,int w,int h);

/// 
/// Inverts the outline of a rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void InvertRectangle(uint8_t *image,int x,int y,int w,int h);

/// 
/// Draws a filled rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void DrawFilledRectangle(uint8_t *image,int x,int y,int w,int h);

/// 
/// Erases a filled rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void EraseFilledRectangle(uint8_t *image,int x,int y,int w,int h);

/// 
/// Inverts a filled rectangle with the upper left corner at pixel position x,y
/// that is width pixels wide and height pixels high.
///
/// \param image A pointer to the pixel data for the display. The
///              display consists of a total of 1024 bytes, or 8 rows
///              of 128 bytes each. 
/// \param x The X coordinate of the upper left corner.
/// \param y The Y coordinate of the upper left corner.
/// \param width The width of the rectangle in pixels.
/// \param height The height of the rectangle in pixels.
///
void InvertFilledRectangle(uint8_t *image,int x,int y,int w,int h);

#endif

