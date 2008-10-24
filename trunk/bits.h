#ifndef _BITS_H
#define _BITS_H

#include <algorithm>
#include <string.h>

class Bits
{
public:
//swap bytes only for LITTLE ENDIAN
static inline unsigned short SwapBytes(unsigned short buf)
{
	return ((buf>>8)&0xff) | ((buf << 8)&0xff00);
};

static inline unsigned int SwapBytes(unsigned int buf)
{
	return((buf & 0xff)<<24) | ((buf & 0xff00)<<8) | ((buf & 0xff0000)>>8) | ((buf >> 24) & 0xff);
};

static inline void SwapBytes(unsigned char* start,unsigned int number)
{
	register int i = 0;
   	register int j = number-1;
   	while (i<j)
  	{
   		std::swap(start[i], start[j]);
      	i++, j--;
   	}
};

static inline void SetBit(unsigned char buf, const unsigned int pos)
{
	buf = buf | ( 0x00000001 << (8-pos) );
};

static inline void SetBit(unsigned int buf, const unsigned int pos)
{
	buf = buf | ( 0x00000001 << (32-pos) );
};

static inline void ClearBit(unsigned char buf,const unsigned int pos)
{
	buf = buf & ~( 0x00000001 << (8-pos) );
};

static inline void ClearBit(unsigned int buf,const unsigned int pos)
{
	buf = buf & ~( 0x00000001 << (32-pos) );
};


////sets the first size bytes of the dest with the integer swapped in network order
static inline void memset_int(unsigned char* dest,unsigned int integer,unsigned int size)
{
	integer = SwapBytes(integer);
    unsigned char* byte = reinterpret_cast<unsigned char*>(&integer);	
	for(unsigned int i=0;i<size;i++)
	{
		dest[i] = byte[i%4];	
	};
};

/*****************************************/

static inline void memset_short(unsigned char* dest,unsigned short shortint,unsigned int size)
{
	shortint = SwapBytes(shortint);
	unsigned char* byte = reinterpret_cast<unsigned char*> (&shortint);
	for(unsigned int i=0;i<size;i++)
	{
		dest[i] = byte[i%2];
	};
};

static inline unsigned short GetUShortInt(unsigned char *address)
{
	unsigned char _address[2];
	memcpy(_address,address,2);
	SwapBytes(_address,2);
	return *(reinterpret_cast<unsigned short*>(_address));
};

static inline unsigned int GetUInt(unsigned char* address)
{
	unsigned char _address[4];
	memcpy(_address,address,4);
	SwapBytes(address,4);
	return *(reinterpret_cast<unsigned int*>(address));
};

};


#endif
