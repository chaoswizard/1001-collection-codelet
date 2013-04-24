#include "gifPlayOnOSD.h"
#include "testData.h"


BOOL  gifgetCurFrameFromList(struct_gifBmpBuf *bmplistHead,struct_gifBmpBuf **bmpData,int frameIdx)
{
	int  curIdx=0;
	struct_gifBmpBuf * curBmpCell=NULL;
	if(NULL == bmplistHead) {return FALSE;}

	curBmpCell = bmplistHead;
	for(curIdx=0;curIdx<frameIdx;curIdx++) {
		if (NULL!=curBmpCell) {
			curBmpCell = curBmpCell->nextBmp;
		} else {
			break;
		}
	}

	if ((curIdx == frameIdx)&&(NULL!=curBmpCell) ) {
		(*bmpData) = curBmpCell;
		return TRUE;
	} else {
		return FALSE;
	}
	
}

#define  SRC_IS_FILE
#define OUT_IS_FILE
void main()
{
	struct tag_gifBmpList * bmpList=NULL;
	struct_gifBmpBuf *curbmp;
	int idx=0,total=0,inputCh =0;
	BOOL isRepeat;
	
#ifdef OUT_IS_FILE
	gif_SetDecodeOutputPath("..\\BMPTRAN\\STRM");
       #ifdef SRC_IS_FILE
	total=gif_CreateBmpPlayList("..\\5328e0dc.gif",&bmpList,0,TRUE,TRUE);// 5328e0dc.gif
       #else
	total=gif_CreateBmpPlayList(GifTestData,&bmpList,sizeof(GifTestData),FALSE,TRUE);// 
      #endif
#else
       #ifdef SRC_IS_FILE
	total=gif_CreateBmpPlayList("..\\fcceb99f.gif",&bmpList,0,TRUE,FALSE);// 
       #else
	total=gif_CreateBmpPlayList(GifTestData,&bmpList,sizeof(GifTestData),FALSE,FALSE);// 
      #endif
#endif

#if  0
	isRepeat = FALSE;
	while(inputCh!='$') {
		
		inputCh=getch();
		if(inputCh == 's') {
			isRepeat = TRUE;
		} else if (inputCh == 'i') {
			isRepeat = FALSE;
		}
		if (gifgetCurFrameFromList(bmpList->allBmpListHead,&curbmp,idx)) {
			printf("Successful!%d___%s  Len=%d  delay=%d\n",idx,curbmp->bmpData,\
				curbmp->dataLength,curbmp->delayTime);
		} else {
			printf("Failed!_%d\n",idx);
		}
		idx++;

		if(idx>=total) {
			idx = 0;
			if(!isRepeat) {
				break;
			} else {
				system("@clear");
			}
		}
	}
#endif
	gif_DestoryBmpPlayList(&bmpList);
}



