#include "gifDecode.h"



#define WX_GIF_DEBUG
#define   PATH_MAXLEN_DECODE   30
#define   NAME_MAXLEN_DECODE   10



static struct  tag_gifgce    gif89a_gce   =   {   -1,   -1,   -1,   0   };   
static struct  tag_gifsdesc gif_sdesc;
static BYTE gifOutfilePath[PATH_MAXLEN_DECODE];

static BOOL         verbose = FALSE;   
static BOOL         showComment= FALSE;   


static   int   LWZ_ReadByte   (   struct BYTESTREAM    *fd,   int   flag,   int   input_code_size   );   
static   int   LWZ_GetCode   (   struct BYTESTREAM    *fd,   int   code_size,   int   flag   );   
static int   gif_Decode(struct BYTESTREAM   *srcStream,  struct tag_gifBmpList *outputList);

static   void   gif_ReadImage   ( struct BYTESTREAM   *fd, struct BYTESTREAM   *desBmpStrm,  int   len,   int   height,   RGBQUAD   *cmap,    int   bpp,   int   interlace,   int   ignore);   
static   int   gif_GetColorMap   (   struct BYTESTREAM    *fd,   int   number,   RGBQUAD   *b);   
static   int   gif_DoExtension   (   struct BYTESTREAM    *fd,   int   label   );   
static   int   gif_GetDataBlock   (   struct BYTESTREAM    *fd,   unsigned   char     *buf   );   

//================================================
void gif_SetDecodeOutputPath(BYTE * outputfile)
{
	int strLen= 0;

	strLen = strlen(outputfile)+1;
	
	memset(gifOutfilePath,'\0',PATH_MAXLEN_DECODE);
	memcpy(gifOutfilePath,outputfile,(strLen<PATH_MAXLEN_DECODE)?strLen:(PATH_MAXLEN_DECODE));
}
int gif_CreateBmpPlayList(BYTE *srcDataOrName,struct_gifBmpList **outputbmpList,DWORD srcArraySize,BOOL srcIsFile,BOOL outputIsFile)
{
	struct BYTESTREAM    *srcStream=NULL;
	int  decodenum=0;
	if (srcIsFile) {
		if(!Create_ByteStrm(&srcStream,srcDataOrName , 0, STRM_FILE_R)){//  "..\\3_2.gif"
			return 0;
		}
	} else {
		if(!Create_ByteStrm(&srcStream,srcDataOrName , srcArraySize, STRM_BUF_S)){
			return 0;
		}
	}

	if (NULL == srcStream) {
		return 0;
	}
	
	(*outputbmpList)=(struct tag_gifBmpList *)malloc(sizeof(struct tag_gifBmpList));
	if (NULL == (*outputbmpList)){
		printf("bmplist Error\n");
		return 0;
	}
	(*outputbmpList)->allBmpListHead = NULL;
	(*outputbmpList)->nframe = 0;
	(*outputbmpList)->isFile = outputIsFile;
	decodenum=gif_Decode(srcStream,(*outputbmpList));
	srcStream->Close(&srcStream,TRUE);
	return decodenum;
	
}

static BOOL gif_AddOneBmpToPlayList(struct  tag_gifBmpList *giflist,void *frameData,DWORD  length,int delayTime)
{
	struct  tag_gifBmpBuf *newbmpCell =NULL;
	struct  tag_gifBmpBuf *bmpListHeadBackup =NULL;
	int filenamelen =0;
	
	if(NULL == giflist){
		return FALSE;
	}

	newbmpCell = (struct  tag_gifBmpBuf*)malloc(sizeof(struct  tag_gifBmpBuf));

	if(NULL==newbmpCell){
		return FALSE;
	}

	if(giflist->isFile) {
		filenamelen = strlen(frameData);
		newbmpCell->bmpData=(BYTE*)malloc(filenamelen+1);
		memset(newbmpCell->bmpData,'\0',filenamelen+1);
		memcpy(newbmpCell->bmpData,frameData,filenamelen);
	} else {
		newbmpCell->bmpData=(BYTE*)frameData;
	}
	newbmpCell->dataLength=length;
	//if(0>delayTime) {delayTime=0;}//delay time will less than Zero
	newbmpCell->delayTime = delayTime;
	newbmpCell->nextBmp =NULL;
	
	if (NULL==giflist->allBmpListHead){
		giflist->allBmpListHead= newbmpCell;
		giflist->nframe =1;
	}else{
		bmpListHeadBackup=giflist->allBmpListHead;

		while(NULL!=(giflist->allBmpListHead->nextBmp)){
			giflist->allBmpListHead = giflist->allBmpListHead->nextBmp;
		}
		giflist->allBmpListHead->nextBmp = newbmpCell;
		
		giflist->allBmpListHead = bmpListHeadBackup;
		giflist->nframe += 1;
	}

	return TRUE;
}

BOOL gif_DestoryBmpPlayList(struct_gifBmpList  **gifList)
{
	struct  tag_gifBmpBuf *bmpListHeadBackup =NULL;
	BOOL isFile=FALSE;

	if (NULL ==(*gifList)){
		return FALSE;
	}

	isFile = (*gifList)->isFile;
	while(NULL!=((*gifList)->allBmpListHead)) {
		bmpListHeadBackup = (*gifList)->allBmpListHead;
		(*gifList)->allBmpListHead = (*gifList)->allBmpListHead->nextBmp;
		if(NULL!=bmpListHeadBackup->bmpData) {
#ifndef WX_GIF_DEBUG
			if(isFile) {
				remove(bmpListHeadBackup->bmpData);
			} 
#endif
			free(bmpListHeadBackup->bmpData);//free data
		}
		free(bmpListHeadBackup);//free cell
	}

	free(*gifList);//free list
	(*gifList) = NULL;
	return TRUE;
}
//================================================

int   gif_Decode(struct BYTESTREAM   *srcStream,  struct tag_gifBmpList *outputList)
  {   
	struct BYTESTREAM   *desBmpStrm=NULL;   
	BYTE  outputBmpName[NAME_MAXLEN_DECODE+PATH_MAXLEN_DECODE];
	int gifFrameCount=0;

	BYTE  testDump[20];
  	BYTE   buf[16];   
  	BYTE   c;   
  	static   RGBQUAD   localColorMap[MAXSIZE_COLORMAP];   
  	int   useGlobalColormap;   
  	int   bitPixel;    
  	char   version[4]; 
		
	gifFrameCount=0;

  	if   (!ReadOK(srcStream,buf,6))   
  	Print_errorMsg("error   reading   magic   number"   );   
    
  	if   (strncmp((char   *)buf,"GIF",3)   !=   0)   
  	Print_errorMsg("not   a   GIF   file"   );   
    
  	strncpy(version,   (char   *)buf   +   3,   3);   
  	version[3]   =   '\0';   
    
  	if   ((strcmp(version,   "87a")   !=   0)   &&   (strcmp(version,   "89a")   !=   0))   
  	Print_errorMsg("bad   version   number,   not   '87a'   or   '89a'"   );   
    
  	if   (!   ReadOK(srcStream,buf,7))   
  	Print_errorMsg("failed   to   read   screen   descriptor"   );   
    
  	gif_sdesc.Width       =   MU8_TO_U16(buf[0],buf[1]);   
  	gif_sdesc.Height     =   MU8_TO_U16(buf[2],buf[3]);   
  	gif_sdesc.BitPixel     =   2<<(buf[4]&0x07);   
  	gif_sdesc.ColorResolution   =   (((buf[4]&0x70)>>3)+1);   
  	gif_sdesc.Background   =   buf[5];   
  	gif_sdesc.AspectRatio   =   buf[6];   //screen height:width
    
  	if   (BitSet(buf[4],   LOCALCOLORMAP))  
  	{ /*   Global   Colormap   */  
//  		printf("gif_sdesc.BitPixel is %d\n,gif_sdesc.Width is %d\n,gif_sdesc.Height is %d\n",gif_sdesc.BitPixel,gif_sdesc.Width,gif_sdesc.Height);
		if   (gif_GetColorMap(srcStream,gif_sdesc.BitPixel,   gif_sdesc.ColorMap))   
  		Print_errorMsg("error   reading   global   colormap"   );   
  	}   
 
  	for   (;;)  
  	{   
  		if   (!ReadOK(srcStream,&c,1))   
  		Print_errorMsg("EOF   /   read   error   on   image   data"   );   
  		if   (c   ==   ';')   
		{   /*   GIF   terminator   */   
  			//if   (gifFrameCount   <   imageNumber)
			//{   
  			//	fprintf(stderr,   "only   %d   image%s   found   in   file\n",   
 	 		//	gifFrameCount,   gifFrameCount>1?"s":""   );   
  			//	exit(1);   
  			//}   
   			printf("image count is %d\n",gifFrameCount);
  			return gifFrameCount;   
  		}      
  		if   (c   ==   '!')   
		{   /*   Extension   */   
 	 		if   (!ReadOK(srcStream,&c,1))   
  			Print_errorMsg("OF   /   read   error   on   extention   function   code");   
  			gif_DoExtension(srcStream,   c);   
  			continue;   
  		}   
    
  		if   (c   !=   ',')  
		{   /*   Not   a   valid   start   character   */   
  			fprintf(stderr,"bogus   character   0x%02x,   ignoring\n",   (int)   c   );   
  			continue;   
  		}   
    
  		++gifFrameCount;   
    
  		if   (!   ReadOK(srcStream,buf,9))   
  		Print_errorMsg("couldn't   read   left/top/width/height");   
    
  		useGlobalColormap   =   !   (buf[8]   &   LOCALCOLORMAP);   
    
  		bitPixel   =   1<<((buf[8]&0x07)+1);   
//==================================================
		if(outputList->isFile) {
			sprintf(outputBmpName,"%s%d.bmp",gifOutfilePath,gifFrameCount);
			if(!Create_ByteStrm(&desBmpStrm, outputBmpName, 0, STRM_FILE_W)) {
				return (gifFrameCount-1);
			}
		}else{
			if(!Create_ByteStrm(&desBmpStrm, NULL, 0, STRM_BUF_D)) {
				return (gifFrameCount-1);
			}
		}
		if(NULL==desBmpStrm){
			return (gifFrameCount-1);
		}
//==================================================
  		if   (!   useGlobalColormap) {   
  			if   (gif_GetColorMap(srcStream,   bitPixel,   localColorMap))   
  				Print_errorMsg("error   reading   local   colormap"   );   
  			gif_ReadImage(srcStream,   desBmpStrm,MU8_TO_U16(buf[4],buf[5]),\
	  			MU8_TO_U16(buf[6],buf[7]),localColorMap,   bitPixel,\
	  			buf[8]&INTERLACE, FALSE );  
  		} else  {   
  			gif_ReadImage(srcStream,  desBmpStrm, MU8_TO_U16(buf[4],buf[5]),\
	  			MU8_TO_U16(buf[6],buf[7]),gif_sdesc.ColorMap,gif_sdesc.BitPixel,\
	  			buf[8]&INTERLACE,  FALSE);   
  		}   
//==================================================
		sprintf(testDump,"WWW%d.txt",gifFrameCount);
		desBmpStrm->InitDumpFile(desBmpStrm,testDump);
		desBmpStrm->Seek(desBmpStrm,0,SEEK_SET);
		desBmpStrm->Dump(desBmpStrm,-1);
		desBmpStrm->CloseDumpFile(desBmpStrm);
		if(outputList->isFile) {
			gif_AddOneBmpToPlayList(outputList,outputBmpName,\
				desBmpStrm->GetSize(desBmpStrm),gif89a_gce.delayTime);
			desBmpStrm->Close(&desBmpStrm,TRUE);
		} else {
			gif_AddOneBmpToPlayList(outputList,desBmpStrm->handle.Array,\
				desBmpStrm->GetSize(desBmpStrm),gif89a_gce.delayTime);
			desBmpStrm->Close(&desBmpStrm,FALSE);
		}
		desBmpStrm = NULL;
//==================================================
  	}  
	return gifFrameCount;
  }   

   
 static   int   gif_GetColorMap( struct BYTESTREAM  *srcStream,   int   number,   RGBQUAD   *buffer)
  {   
  	int   i;   
  	unsigned   char   rgb[3];   

 	 for   (i   =   0;   i   <   number;   ++i,   buffer++)  
	 {   
  		if   (!   ReadOK(srcStream,   rgb,   sizeof(rgb)))   
 		Print_errorMsg("bad   colormap"   );   
  		buffer->rgbBlue=   rgb[0];   
  		buffer->rgbGreen=   rgb[1];   
  		buffer->rgbRed=   rgb[2];   
  		buffer->rgbReserved=   0;   
	 }   
  	return   0;   
  }   
  
  static   int   gif_DoExtension( struct BYTESTREAM   *srcStream,   int   label)
  {   
  	static   char buf[256];   
  	char *str;   
    
  	switch(label)   
	{   
  		case   0x01: /*   Plain   Text   Extension   */   
  			str   =   "Plain   Text   Extension";   
#if  0
			if   (gif_GetDataBlock(srcStream,   (unsigned   char*)   buf)   ==   0)   
			;   

			lpos =   LM_to_uint(buf[0],   buf[1]);   
			tpos =   LM_to_uint(buf[2],   buf[3]);   
			width =   LM_to_uint(buf[4],   buf[5]);   
			height   =   LM_to_uint(buf[6],   buf[7]);   
			cellw =   buf[8];   
			cellh =   buf[9];   
			foreground   =   buf[10];   
			background   =   buf[11];   

			while   (gif_GetDataBlock(srcStream,   (unsigned   char*)   buf)   !=   0)  
			{   
			PPM_ASSIGN(image[ypos][xpos],   
			cmap[CM_RED][v],   
			cmap[CM_GREEN][v],   
			cmap[CM_BLUE][v]);   
			++index;   
			}   
			return   FALSE;   
#else   
			break;   
#endif   
 		 case   0xff: /*   Application   Extension   */   
  			str   =   "Application   Extension";   
  			gif_GetDataBlock(srcStream,   (BYTE*)buf);   
 			 if   (showComment)
		 	{   
  				fprintf(stderr,   "Application   Extension:   %c%c%c%c%c%c%c%c   ",   
  				buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7]);   
  				fprintf(stderr,   "   Authentication   Code=)%02x   %02x   %02x\n",   
  				buf[8],   buf[9],   buf[10]);   
  			}   
  			break;   
  		case   0xfe: /*   Comment   Extension   */   
  			str   =   "Comment   Extension";   
  			while   (gif_GetDataBlock(srcStream,   (BYTE*)   buf)   !=   0)  
			{   
  				if   (showComment)   
  				fprintf(stderr,"gif   comment:   %s\n",   buf   );   
  			}   
 			 return   FALSE;   
 		case   0xf9: /*   Graphic   Control   Extension   */   
  			str   =   "Graphic   Control   Extension";   
  			(void)   gif_GetDataBlock(srcStream,   (BYTE*)   buf);   
  			gif89a_gce.disposal         =   (buf[0]   >>   2)   &   0x7;   
  			gif89a_gce.inputFlag       =   (buf[0]   >>   1)   &   0x1;   
  			gif89a_gce.delayTime       =   MU8_TO_U16(buf[1],buf[2]);   
  			if   ((buf[0]   &   0x1)   !=   0)   
  			gif89a_gce.transparent   =   buf[3];   
    
  			while   (gif_GetDataBlock(srcStream,   (BYTE*)   buf)   !=   0)   
  			;   
  			return   FALSE;   
		default:   
  			str   =   buf;   
  			sprintf(buf,   "UNKNOWN   (0x%02x)",   label);   
  			break;   
  	}   
    
  	//fprintf(stderr,"got   a   '%s'   extension\n",   str   );   
    
  	while   (gif_GetDataBlock(srcStream,   (BYTE*)buf)   !=   0)   
  	;   
    
  	return   FALSE;   
  }

  
  BOOL         ZeroDataBlock   =   FALSE;   
    
  static   int   gif_GetDataBlock( struct BYTESTREAM   *fd,   unsigned   char     *buf)
  {   
  	unsigned   char count;   
    
  	if   (!   ReadOK(fd,&count,1))   
	{   
  		fprintf(stderr,"error   in   getting   DataBlock   size\n"   );   
  		return   -1;   
  	}   
    
  	ZeroDataBlock   =   count   ==   0;   
    
 	if   ((count   !=   0)   &&   (!   ReadOK(fd,   buf,   count)))   
	{   
  		fprintf(stderr,"error   in   reading   DataBlock\n"   );   
  		return   -1;   
  	}   
    
  	return   count;   
  } 

  
  static   int   LWZ_GetCode( struct BYTESTREAM   *fd,   int   code_size,   int   flag)
  {   
  	static   unsigned   char buf[280];   
  	static   int curbit,   lastbit,   done,   last_byte;   
  	int i,   j,   ret;   
  	unsigned   char count;   
    
  	if   (flag)   
	{   
  		curbit   =   0;   
  		lastbit   =   0;   
  		done   =   FALSE;   
  		return   0;   
  	}   
    
  	if   (   (curbit+code_size)   >=   lastbit)  
	{   
  		if   (done)   
		{   
  			if   (curbit   >=   lastbit)   
  			Print_errorMsg("ran   off   the   end   of   my   bits"   );   
  			return   -1;   
  		}   
 		buf[0]   =   buf[last_byte-2];   
  		buf[1]   =   buf[last_byte-1];   
    
 		if   ((count   =   gif_GetDataBlock(fd,   &buf[2]))   ==   0)   
  		done   =   TRUE;   
    
  		last_byte   =   2   +   count;   
  		curbit   =   (curbit   -   lastbit)   +   16;   
  		lastbit   =   (2+count)*8   ;   
  	}   
    
  	ret   =   0;   
  	for   (i   =   curbit,   j   =   0;   j   <   code_size;   ++i,   ++j)   
  	ret   |=   ((buf[   i   /   8   ]   &   (1   <<   (i   %   8)))   !=   0)   <<   j;   
    
  	curbit   +=   code_size;   
    
 	return   ret;   
  }

  
  static   int   LWZ_ReadByte( struct BYTESTREAM   *fd,   int   flag,   int   input_code_size)
  {   
  	static   int fresh   =   FALSE;   
  	int code,   incode;   
  	static   int code_size,   set_code_size;   
  	static   int max_code,   max_code_size;   
  	static   int firstcode,   oldcode;   
  	static   int clear_code,   end_code;   
  	static   int table[2][(1<<   MAX_LWZ_BITS)];   
  	static   int stack[(1<<(MAX_LWZ_BITS))*2],   *sp;   
  	register   int i;   
    
  	if   (flag)   
	{   
  		set_code_size   =   input_code_size;   
 		code_size   =   set_code_size+1;   
  		clear_code   =   1   <<   set_code_size   ;   
  		end_code   =   clear_code   +   1;   
  		max_code_size   =   2*clear_code;   
  		max_code   =   clear_code+2;   
    
  		LWZ_GetCode(fd,   0,   TRUE);   
    
  		fresh   =   TRUE;   
    
  		for   (i   =   0;   i   <   clear_code;   ++i)   
		{   
  			table[0][i]   =   0;   
  			table[1][i]   =   i;   
  		}   
  		for   (;   i   <   (1<<MAX_LWZ_BITS);   ++i)   
  		table[0][i]   =   table[1][0]   =   0;   
    
  		sp   =   stack;   
    
  		return   0;   
  	}   
	else   if   (fresh)  
	{ 
  		fresh   =   FALSE;   
  		do   {   
  				firstcode   =   oldcode   =   
  				LWZ_GetCode(fd,   code_size,   FALSE);   
  			}   while   (firstcode   ==   clear_code);   
  		return   firstcode;   
  	}   
    
  	if   (sp   >   stack)   
  	return   *--sp;   
    
  	while   ((code   =   LWZ_GetCode(fd,   code_size,   FALSE))   >=   0)  
	{   
  		if   (code   ==   clear_code)   
		{   
  			for   (i   =   0;   i   <   clear_code;   ++i)   
			{   
  				table[0][i]   =   0;   
  				table[1][i]   =   i;   
  			}   
  			for   (;   i   <   (1<<MAX_LWZ_BITS);   ++i)   
  			table[0][i]   =   table[1][i]   =   0;   
  			code_size   =   set_code_size+1;   
  			max_code_size   =   2*clear_code;   
  			max_code   =   clear_code+2;   
  			sp   =   stack;   
  			firstcode   =   oldcode   =   
  			LWZ_GetCode(fd,   code_size,   FALSE);   
  			return   firstcode;   
  		}   
		else   if   (code   ==   end_code)   
		{   
  			int count;   
  			unsigned   char       buf[260];   
    
  			if   (ZeroDataBlock)   
  			return   -2;   
    
  			while   ((count   =   gif_GetDataBlock(fd,   buf))   >   0)   
  			;   
    
  			if   (count   !=   0)   
  			fprintf(stderr,"missing   EOD   in   data   stream   (common   occurence)\n");   
  			return   -2;   
 		}   
    
 		 incode   =   code;   
    
  		if   (code   >=   max_code)  
		{   
  			*sp++   =   firstcode;   
  			code   =   oldcode;   
  		}   
    
  		while   (code   >=   clear_code)   
		{   
  			*sp++   =   table[1][code];   
 			 if   (code   ==   table[0][code])   
  			Print_errorMsg("circular   table   entry   BIG   ERROR");   
  			code   =   table[0][code];   
 		}   
    
             *sp++   =   firstcode   =   table[1][code];   
    
             if   ((code   =   max_code)   <(1<<MAX_LWZ_BITS))   
		{   
     			table[0][code]   =   oldcode;   
 			 table[1][code]   =   firstcode;   
  			++max_code;   
  			if   ((max_code   >=   max_code_size)   &&   
  			(max_code_size   <   (1<<MAX_LWZ_BITS)))   
  			{   
  				max_code_size   *=   2;   
 			 	++code_size;   
 		 	}   
  		}   
    
 		 oldcode   =   incode;   
    
  		if   (sp   >   stack)   
  		return   *--sp;   
  	}   
  	return   code;   
  } 

  
  static   void   gif_ReadImage( struct BYTESTREAM   *fd, struct BYTESTREAM   *desBmpStrm,  int   len,   int   height,   RGBQUAD   *cmap,   
    int   bpp,   int   interlace,   int   ignore)
  {   
	DWORD   bmpColorBitCount = 8;   
	DWORD   bmpScanLineLength = 0;   
  	unsigned   char c;   
  	int tempCh;   
  	int xpos   =   0,   ypos   =   0,   pass   =   0;   
  	unsigned   char   *scanline;   
    
  /*   
  **     Initialize   the   Compression   routines   
  */   
  	if   (!   ReadOK(fd,&c,1))   
  	Print_errorMsg("EOF   /   read   error   on   image   data"   );   
    
  	if   (LWZ_ReadByte(fd,   TRUE,   c)   <   0)   
  	Print_errorMsg("error   reading   image"   );   
    
  /*   
  **     If   this   is   an   "uninteresting   picture"   ignore   it.   
  */   
  	if   (ignore)   
	{   
  		if   (verbose)   
 		 fprintf(stderr,"skipping   image...\n"   );   
    
  		while   (LWZ_ReadByte(fd,   FALSE,   c)   >=   0)   
  		;   
  		return;   
  	}   
 	if   ((scanline=   (unsigned   char   *)malloc(len))   ==   NULL)   
  	Print_errorMsg("couldn't   alloc   space   for   image"   );   
    
    
  	if   (verbose)   
  	fprintf(stderr,"reading   %d   by   %d%s   GIF   image\n", 	len,   height,   interlace   ?   "   interlaced"   :   ""   );   
    
  	bmp_InitHeader(desBmpStrm,len,   height,   bpp,  FALSE, cmap,&bmpColorBitCount,&bmpScanLineLength);   
  /*   Fill   the   whole   file   with   junk   */   
  	for(tempCh=   0;   tempCh<height;   tempCh++)   
		desBmpStrm->Write(desBmpStrm,scanline,   1,   (int)bmpScanLineLength);  
	
  	while   (ypos<height   &&   (tempCh   =   LWZ_ReadByte(fd,FALSE,c))   >=   0)   
	{   
  		switch(bmpColorBitCount)
		{   
  			case   1:   
  				if(tempCh)   
  				scanline[xpos>>3]   |=   128   >>   (xpos&7);   
  				else   
  				scanline[xpos>>3]   &=   0xff7f   >>   (xpos&7);   
  				break;   
  			case   4:   
  				if(xpos&1)   
  				scanline[xpos>>1]   |=   tempCh&15;   
  				else   
  				scanline[xpos>>1]   =   (tempCh&15)   <<   4;   
  				break;   
 			case   8:   
  				scanline[xpos]=   tempCh;   
  				break;   
  		}   
  		++xpos;   
  		if   (xpos   ==   len)   
		{   
  			desBmpStrm->Seek(desBmpStrm,   -(ypos+1)*bmpScanLineLength,   SEEK_END);   
			desBmpStrm->Write(desBmpStrm,scanline,   1,   (int)bmpScanLineLength);
  			xpos   =   0;   
  			if   (interlace)   
			{   
  				static   int   dpass[]=   {8,8,4,2};   
  				ypos   +=   dpass[pass];   
  				if   (ypos   >=   height)   
				{   
  				static   int   restart[]=   {0,4,2,1,32767};   
  				ypos=   restart[++pass];   
  				}   
  			}   
			else   
  			++ypos;   
 		 }   
  	} 
	
  	if(LWZ_ReadByte(fd,   FALSE,c)   >=   0)   
  		fprintf(stderr,"too   much   input   data,   ignoring   extra...\n");   
  }   

/********************************Show OkList AdPic**********************************/


