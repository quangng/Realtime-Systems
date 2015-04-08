#include "Graphics.h"

#include <stdbool.h>
#include <string.h>

#define ScreenColumns 128
#define ScreenRows 8
#define ScreenSize (ScreenColumns*ScreenRows)

static inline bool IsSpanCompletelyInside(int start,int len,int max)
{
	if(start<0) return false;
	if(start+len>max) return false;
	return true;
}

static inline bool IsSpanCompletelyOutside(int start,int len,int max)
{
	if(start>=max) return true;
	if(start+len<=0) return true;
	return false;
}

static inline bool IsCompletelyInside(int x,int y,int w,int h,int clipw,int cliph)
{
	return IsSpanCompletelyInside(x,w,clipw)&&IsSpanCompletelyInside(y,h,cliph);
}

static inline bool IsCompletelyOutside(int x,int y,int w,int h,int clipw,int cliph)
{
	return IsSpanCompletelyOutside(x,w,clipw)||IsSpanCompletelyOutside(y,h,cliph);
}

static inline void AdjustSpan(int *start,int *len,int max)
{
	if(*start<0) { (*len)+=*start; *start=0; }
	if(*start+*len>max) *len=max-*start;
}

static inline bool ClipLine(int *u,int *v,int *len,int clipu,int clipv)
{
	if(IsCompletelyOutside(*u,*v,*len,1,clipu,clipv)) return false;
	AdjustSpan(u,len,clipu);
	return true;
}

static inline bool ClipRectangle(int *x,int *y,int *w,int *h,int clipw,int cliph)
{
	if(IsCompletelyOutside(*x,*y,*w,*h,clipw,cliph)) return false;
	AdjustSpan(x,w,clipw);
	AdjustSpan(y,h,cliph);
	return true;
}




typedef void DrawPixelColumnFunction(uint8_t *ptr,uint8_t data);
typedef void DrawPixelColumnsFunction(uint8_t *ptr,uint8_t data,unsigned int n);
typedef void DrawPixelFunction(uint8_t *image,int x,int y);
typedef void DrawHorizontalLineFunction(uint8_t *image,int x,int y,int width);
typedef void DrawVerticalLineFunction(uint8_t *image,int x,int y,int height);

static inline void DrawPixelColumn(uint8_t *ptr,uint8_t data) { *ptr|=data; }

static inline void ErasePixelColumn(uint8_t *ptr,uint8_t data) { *ptr&=~data; }

static inline void InvertPixelColumn(uint8_t *ptr,uint8_t data) { *ptr^=data; }

static inline void DrawPixelColumns(uint8_t *ptr,uint8_t data,unsigned int n)
{
	uint32_t val=data*0x01010101;
	if(((uintptr_t)ptr)&3)
	{
		unsigned int first=4-(((uintptr_t)ptr)&3);
		for(int i=0;i<first;i++) *ptr++|=val;
		n-=first;
	}

	uint32_t *ptr32=(uint32_t *)ptr;
	for(int i=0;i<n/4;i++) *ptr32++|=val;

	if(n&3)
	{
		for(int i=0;i<(n&3);i++) *ptr++|=val;
	}
}

static inline void ErasePixelColumns(uint8_t *ptr,uint8_t data,unsigned int n)
{
	uint32_t val=~(data*0x01010101);
	if(((uintptr_t)ptr)&3)
	{
		unsigned int first=4-(((uintptr_t)ptr)&3);
		for(int i=0;i<first;i++) *ptr++&=val;
		n-=first;
	}

	uint32_t *ptr32=(uint32_t *)ptr;
	for(int i=0;i<n/4;i++) *ptr32++&=val;

	if(n&3)
	{
		for(int i=0;i<(n&3);i++) *ptr++&=val;
	}
}

static inline void InvertPixelColumns(uint8_t *ptr,uint8_t data,unsigned int n)
{
	uint32_t val=data*0x01010101;
	if(((uintptr_t)ptr)&3)
	{
		unsigned int first=4-(((uintptr_t)ptr)&3);
		for(int i=0;i<first;i++) *ptr++^=val;
		n-=first;
	}

	uint32_t *ptr32=(uint32_t *)ptr;
	for(int i=0;i<n/4;i++) *ptr32++^=val;

	if(n&3)
	{
		for(int i=0;i<(n&3);i++) *ptr++^=val;
	}
}




void ClearScreen(uint8_t *image)
{
	memset(image,0,ScreenSize);
}

void FillScreen(uint8_t *image)
{
	for(int i=0;i<ScreenSize;i++) image[i]=255;
}

void DrawPixel(uint8_t *image,int x,int y)
{
	if(x<0 || y<0 || x>=ScreenColumns || y>=ScreenRows*8) return;
	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	DrawPixelColumn(ptr,1<<(y&7));
}

void ErasePixel(uint8_t *image,int x,int y)
{
	if(x<0 || y<0 || x>=ScreenColumns || y>=ScreenRows*8) return;
	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	ErasePixelColumn(ptr,1<<(y&7));
}

void InvertPixel(uint8_t *image,int x,int y)
{
	if(x<0 || y<0 || x>=ScreenColumns || y>=ScreenRows*8) return;
	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	InvertPixelColumn(ptr,1<<(y&7));
}

void DrawHorizontalLine(uint8_t *image,int x,int y,int width)
{
	if(!ClipLine(&x,&y,&width,ScreenColumns,ScreenRows*8)) return;

	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	uint8_t val=1<<(y&7);
	DrawPixelColumn(ptr,val);
}

void EraseHorizontalLine(uint8_t *image,int x,int y,int width)
{
	if(!ClipLine(&x,&y,&width,ScreenColumns,ScreenRows*8)) return;

	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	uint8_t val=1<<(y&7);
	ErasePixelColumn(ptr,val);
}

void InvertHorizontalLine(uint8_t *image,int x,int y,int width)
{
	if(!ClipLine(&x,&y,&width,ScreenColumns,ScreenRows*8)) return;

	uint8_t *ptr=image+x+ScreenColumns*(y>>3);
	uint8_t val=1<<(y&7);
	InvertPixelColumn(ptr,val);
}

static inline void GenericDrawVerticalLine(uint8_t *image,int x,int y,int height,DrawPixelColumnFunction drawfunc)
{
	if(!ClipLine(&y,&x,&height,ScreenRows*8,ScreenColumns)) return;

	unsigned int y1=y,y2=y+height;
	unsigned int row1=y1>>3,row2=y2>>3;
	uint8_t *ptr=image+x+row1*ScreenColumns;

	if(row1==row2)
	{
		drawfunc(ptr,((1<<(y1&7))-1)^((1<<(y2&7))-1));
	}
	else
	{
		if(y1&7)
		{
			drawfunc(ptr,~((1<<(y1&7))-1));
			ptr+=ScreenColumns;
			row1++;
		}

		for(int row=row1;row<row2;row++)
		{
			drawfunc(ptr,255);
			ptr+=ScreenColumns;
		}

		if(y2&7)
		{
			drawfunc(ptr,(1<<(y2&7))-1);
		}
	}
}

void DrawVerticalLine(uint8_t *image,int x,int y,int height)
{ GenericDrawVerticalLine(image,x,y,height,DrawPixelColumn); }

void EraseVerticalLine(uint8_t *image,int x,int y,int height)
{ GenericDrawVerticalLine(image,x,y,height,ErasePixelColumn); }

void InvertVerticalLine(uint8_t *image,int x,int y,int height)
{ GenericDrawVerticalLine(image,x,y,height,InvertPixelColumn); }

static inline void GenericDrawLine(uint8_t *image,int x1,int y1,int x2,int y2,DrawPixelFunction drawfunc)
{
	int dx,dy,xinc,yinc;

	if(x1>x2) { dx=x1-x2; xinc=-1; }
	else { dx=x2-x1; xinc=1; }
	if(y1>y2) { dy=y1-y2; yinc=-1; }
	else { dy=y2-y1; yinc=1; }

	if(dx>=dy)
	{
		int dpr=dy<<1;
		int dpru=dpr-(dx<<1);
		int p=dpr-dx;

		for(;dx>=0;dx--)
		{
			drawfunc(image,x1,y1);
			if(p>0)
			{
				x1+=xinc;
				y1+=yinc;
				p+=dpru;
			}
			else
			{
				x1+=xinc;
				p+=dpr;
			}
		}
	}
	else
	{
		int dpr=dx<<1;
		int dpru=dpr-(dy<<1);
		int p=dpr-dy;

		for(;dy>=0;dy--)
 		{
			drawfunc(image,x1,y1);
			if(p>0)
			{
				x1+=xinc;
				y1+=yinc;
				p+=dpru;
			}
			else
			{
				y1+=yinc;
				p+=dpr;
			}
		}
	}
}

void DrawLine(uint8_t *image,int x1,int y1,int x2,int y2)
{ GenericDrawLine(image,x1,y1,x2,y2,DrawPixel); }

void EraseLine(uint8_t *image,int x1,int y1,int x2,int y2)
{ GenericDrawLine(image,x1,y1,x2,y2,ErasePixel); }

void InvertLine(uint8_t *image,int x1,int y1,int x2,int y2)
{ GenericDrawLine(image,x1,y1,x2,y2,InvertPixel); }

static inline void GenericDrawRectangle(uint8_t *image,int x,int y,int width,int height,DrawHorizontalLineFunction *horizontalfunc,DrawVerticalLineFunction *verticalfunc)
{
	if(width<0 || height<0) return;
	else if(width==1)  verticalfunc(image,x,y,height);
	else if(height==1) horizontalfunc(image,x,y,width);
	else
	{
		horizontalfunc(image,x,y,width);
		horizontalfunc(image,x,y+height-1,width);

		if(height>2)
		{
			verticalfunc(image,x,y,height);
			verticalfunc(image,x+width-1,y,height);
		}
	}
}

void DrawRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawRectangle(image,x,y,width,height,DrawHorizontalLine,DrawVerticalLine); }

void EraseRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawRectangle(image,x,y,width,height,EraseHorizontalLine,EraseVerticalLine); }

void InvertRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawRectangle(image,x,y,width,height,InvertHorizontalLine,InvertVerticalLine); }

static inline void GenericDrawFilledRectangle(uint8_t *image,int x,int y,int width,int height,DrawPixelColumnsFunction *drawfunc)
{
	if(!ClipRectangle(&x,&y,&width,&height,ScreenColumns,ScreenRows*8)) return;

	unsigned int y1=y,y2=y+height;
	unsigned int row1=y1>>3,row2=y2>>3;
	uint8_t *ptr=image+x+row1*ScreenColumns;

	if(row1==row2)
	{
		drawfunc(ptr,((1<<(y1&7))-1)^((1<<(y2&7))-1),width);
	}
	else
	{
		if(y1&7)
		{
			drawfunc(ptr,~((1<<(y1&7))-1),width);
			ptr+=ScreenColumns;
			row1++;
		}

		for(int row=row1;row<row2;row++)
		{
			drawfunc(ptr,255,width);
			ptr+=ScreenColumns;
		}

		if(y2&7)
		{
			drawfunc(ptr,(1<<(y2&7))-1,width);
		}
	}
}

void DrawFilledRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawFilledRectangle(image,x,y,width,height,DrawPixelColumns); }

void EraseFilledRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawFilledRectangle(image,x,y,width,height,ErasePixelColumns); }

void InvertFilledRectangle(uint8_t *image,int x,int y,int width,int height)
{ GenericDrawFilledRectangle(image,x,y,width,height,InvertPixelColumns); }

