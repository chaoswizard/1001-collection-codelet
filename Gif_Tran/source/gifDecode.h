#ifndef __GIFDECODE_H__
#define __GIFDECODE_H__

#include "bmpDecode.c"

 #define    MAXSIZE_COLORMAP             256   
    
   
  #define   MAX_LWZ_BITS             12   
    
  #define   INTERLACE             0x40   
  #define   LOCALCOLORMAP     0x80   
    
  #define   ReadOK(file,buffer,len)   ((file->Read(file,buffer ,   len, 1 )) !=   0)
    

  
struct  tag_gifsdesc {   
                unsigned   int         Width;   
                unsigned   int         Height;   
		RGBQUAD   ColorMap[MAXSIZE_COLORMAP];   
                unsigned   int         BitPixel;   
                unsigned   int         ColorResolution;   
                unsigned   int         Background;   
                unsigned   int         AspectRatio;   
                int             GrayScale;   
};   
  
struct   tag_gifgce{   
                int           transparent;   
                int           delayTime;   
                int           inputFlag;   
                int           disposal;   
};   
//////////////////////////////////////////////////////////
typedef struct  tag_gifBmpBuf {
	BYTE *bmpData;
	DWORD dataLength;
	int delayTime;
	struct  tag_gifBmpBuf *nextBmp;
}struct_gifBmpBuf;

typedef struct tag_gifBmpList {
	struct  tag_gifBmpBuf * allBmpListHead;
	WORD  nframe;
	BOOL isFile;
//--------------------------	
	WORD  originX;
	WORD  originY;
	BOOL isEscape;
	BOOL isRepeat;
}struct_gifBmpList;
//////////////////////////////////////////////////////////
void gif_SetDecodeOutputPath(BYTE * outputfile);
int gif_CreateBmpPlayList(BYTE *srcDataOrName,struct_gifBmpList **outputbmpList,DWORD srcArraySize,BOOL srcIsFile,BOOL outputIsFile);
BOOL gif_DestoryBmpPlayList(struct_gifBmpList  **bmpList);

#endif

