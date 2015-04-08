#include "Serial.h"

#define UART3_LSR (*(volatile uint8_t *)(0x49020000+20))
#define UART3_RBR (*(volatile uint8_t *)(0x49020000+0))

bool AreSerialBytesAvailable()
{
	return (UART3_LSR&0x01)==0x01;
}

bool IsSerialBufferFull()
{
	return (UART3_LSR&0x20)==0;
}

void SendSerialByte(uint8_t byte)
{
	while(IsSerialBufferFull());
	UART3_RBR=byte;
}

uint8_t ReceiveSerialByte()
{
	while(!AreSerialBytesAvailable());
	return UART3_RBR;
}


void PrintSerialString(const char *string)
{
	while(*string) SendSerialByte(*string++);
}

void PrintSerialHexByte(uint8_t byte)
{
	SendSerialByte(Hex((byte>>4)&0x0f));
	SendSerialByte(Hex(byte&0x0f));
}

void PrintSerialHexWord(uint32_t byte)
{
	SendSerialByte(Hex((byte>>28)&0x0f));
	SendSerialByte(Hex((byte>>24)&0x0f));
	SendSerialByte(Hex((byte>>20)&0x0f));
	SendSerialByte(Hex((byte>>16)&0x0f));
	SendSerialByte(Hex((byte>>12)&0x0f));
	SendSerialByte(Hex((byte>>8)&0x0f));
	SendSerialByte(Hex((byte>>4)&0x0f));
	SendSerialByte(Hex(byte&0x0f));
}

char Hex(int val)
{
	if(val>=0&&val<=9) return val+'0';
	else if (val>=10&&val<=15) return val-10+'a';
	else return ' ';
}

