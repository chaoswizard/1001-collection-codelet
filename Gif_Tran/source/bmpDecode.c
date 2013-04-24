#include "bmpDecode.h"


  void   Print_errorMsg(char   *msg)
  {   
  	fprintf(stderr,   "%s\n",   msg);   
  	exit(5);   
  }  


static  DWORD bmp_GetScanLineWidth(WORD   bitcount,   DWORD   wi)
  {   
  	switch   (bitcount)
	{   
  		case   1:   wi=   (wi+31)   >>   3;   break;   
 	       case   4:   wi=   (wi+7)     >>   1;   break;   
  		case   8:   wi=     wi+3;   break;   
  		case   16:wi=   (wi*2)+3;   break;   
  		case   24:wi=   (wi*3)+3;   break;   
  		case   32:return   wi*4;   
  	}   
  	return   wi   &   ~3;   
  }   


  /*  bmp   header   */   
  int   bmp_InitHeader(struct BYTESTREAM   *desBmpStrm,int   width,   int   height,   int   colorCount,   BOOL is8Bmp,RGBQUAD   *cmap,DWORD *bmpColorBitCount,DWORD *bmpScanLineLength)
  {   
	BMP_FILE_HEADER   bmpFileInfo;   
	BMP_HEAD_INFO   bmpHeadInfo;   

  	if (NULL==desBmpStrm){
		return 0;
	}
  /*   Writes   to   the     desBmpStrm   */   
  	if(colorCount>16   ||   is8Bmp) {
	  	bmpHeadInfo.biBitCount=   8;   
	}else   if(colorCount>2) {
	  	bmpHeadInfo.biBitCount=   4;   
	} else  {
	  	bmpHeadInfo.biBitCount=   1;   
	} 
	
  	colorCount=   1   <<   ((int)bmpHeadInfo.biBitCount);   
	
  	bmpHeadInfo.biSize=   sizeof(bmpHeadInfo);  
  	bmpHeadInfo.biWidth=   width;   
  	bmpHeadInfo.biHeight=   height;  
  	bmpHeadInfo.biPlanes=   1;  	
	
  	(*bmpScanLineLength)=   bmp_GetScanLineWidth((WORD)bmpHeadInfo.biBitCount,   (DWORD)bmpHeadInfo.biWidth);   

	bmpHeadInfo.biSizeImage=   bmpHeadInfo.biHeight   *   (*bmpScanLineLength);   	
  	bmpHeadInfo.biClrUsed=   colorCount;  	
  	bmpHeadInfo.biClrImportant=   colorCount;  
//-----------------------------------------------------------	   
 	bmpFileInfo.bfType=0x4d42; /*   MB   */  
  	bmpFileInfo.bfOffBits   =   sizeof(bmpFileInfo)   +   bmpHeadInfo.biSize   +   colorCount*sizeof(RGBQUAD); 
  	bmpFileInfo.bfSize=   bmpFileInfo.bfOffBits   +   bmpHeadInfo.biSizeImage; 

	hton_U16(bmpFileInfo.bfType);//
  	bmpFileInfo.bfReserved1=   0;   
  	bmpFileInfo.bfReserved2=   0;   
	hton_U32(bmpFileInfo.bfSize);
	hton_U32(bmpFileInfo.bfOffBits);

	hton_U32(bmpHeadInfo.biSize);
	hton_U32(bmpHeadInfo.biWidth);
	hton_U32(bmpHeadInfo.biHeight);
	hton_U16(bmpHeadInfo.biPlanes);
	hton_U16(bmpHeadInfo.biBitCount);
  	bmpHeadInfo.biCompression=   0;   
	hton_U32(bmpHeadInfo.biSizeImage);
  	bmpHeadInfo.biXPelsPerMeter=   0;   
  	bmpHeadInfo.biYPelsPerMeter=   0;  
	hton_U32(bmpHeadInfo.biClrUsed);
	hton_U32(bmpHeadInfo.biClrImportant);

  	desBmpStrm->Write(desBmpStrm,&bmpFileInfo,1,sizeof(bmpFileInfo)); 
  	desBmpStrm->Write(desBmpStrm,&bmpHeadInfo, 1,sizeof(bmpHeadInfo));  

	if(colorCount>16   ||   is8Bmp)  {
	  	(*bmpColorBitCount)=   8;   
	} else   if(colorCount>2)  {
	  	(*bmpColorBitCount)=   4;   
	} else   {
		(*bmpColorBitCount)=   1;   
	}
	
  	if(colorCount>0) {
	  	desBmpStrm->Write(desBmpStrm,cmap,   sizeof(RGBQUAD),   colorCount);   
	}
  	return   1;   
}   

