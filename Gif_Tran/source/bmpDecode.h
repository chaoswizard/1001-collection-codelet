#ifndef __BMPDECODE_H__
#define __BMPDECODE_H__

#include "XXByteStrm.c"
#include <string.h>
#include <malloc.h>
//#define  _ENDIAN_BIG_

#define   CM_RED             0   
#define   CM_GREEN               1   
#define   CM_BLUE               2   


#ifdef _ENDIAN_BIG_
#define hton_U16(A)	((A)=((((A)&0xff00)>>8)|((A)&0x00ff)<<8))
#define hton_U32(A)	((A)=((((A)&0xff000000)>>24)|(((A)&0x00ff0000)>>8)|\
		(((A)&0x0000ff00)<<8)|(((A)&0x000000ff)<<24)))
#else
#define hton_U16(A)	/*(A)*/
#define hton_U32(A)	/*(A)*/
#endif


#define   MU8_TO_U16(a,b)           (((b)<<8)|(a))   
#define   BitSet(byte,   bit)             (((byte)   &   (bit))   ==   (bit))   

#pragma pack(1)

typedef struct tagRGBQUAD {
	BYTE rgbRed;
	BYTE rgbGreen;
	BYTE rgbBlue;
	BYTE rgbReserved;
} RGBQUAD;

  typedef   struct   tagBITMAPFILEHEADER   {   
  WORD bfType;   
  DWORD bfSize;   
  WORD bfReserved1;   
  WORD bfReserved2;   
  DWORD bfOffBits;   
  } BMP_FILE_HEADER, *P_BMP_FILE_HEADER;   

typedef struct tagBITMAPINFOHEADER{
  DWORD biSize;
  DWORD  biWidth;
  DWORD  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  DWORD  biXPelsPerMeter;
  DWORD  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BMP_HEAD_INFO, *P_BMP_HEAD_INFO;

#pragma pack()


  int   bmp_InitHeader(struct BYTESTREAM   *desBmpStrm,int   width,   int   height,   int   colorCount,   BOOL is8Bmp,RGBQUAD   *cmap,DWORD *bmpColorBitCount,DWORD *bmpScanLineLength);
  void   Print_errorMsg(char   *msg);

#endif
