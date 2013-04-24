#include "stdio.h"

#define list_get_entry(ptr, type, member)	\
	((type *)((char *)(ptr)+(unsigned long)(&((type *)0)->member)))

struct st_List{
	char first;//4
	short second;//2
	char third;//1
	long fouth;//4
	char fif;//1
};

void main()
{
#if 0
	st_List mylist;
	st_List *pList;
	pList=list_get_entry(&mylist,struct st_List,fouth);

	printf("\n:%p ",pList);
	printf("\n:%p ",&(mylist.fouth));

#else
	unsigned long  CurAddr=0,logicAddr=0,NexAddr=0;
	int CurMemberSize=0,padSize=0;

//////////////////////³õÊ¼»¯///////////////////////////////
	CurAddr=(unsigned long)(&((struct st_List *)0)->first);
	CurMemberSize=sizeof(*(struct st_List *)0).first;

	logicAddr=CurAddr+CurMemberSize;
	printf("\n:%p ",CurAddr);
	printf("\t+%d",CurMemberSize);
//////////////////////¿ªÊ¼///////////////////////
	CurAddr=(unsigned long)(&((struct st_List *)0)->second);
	CurMemberSize=sizeof(*(struct st_List *)0).second;

	if(logicAddr<CurAddr){
		printf("\tÌî³ä%d",(CurAddr - logicAddr));
	}

	logicAddr=CurAddr+CurMemberSize;
	printf("\n:%p ",CurAddr);
	printf("\t+%d",CurMemberSize);
///////////////////////////////////////////////////
	CurAddr=(unsigned long)(&((struct st_List *)0)->third);
	CurMemberSize=sizeof(*(struct st_List *)0).third;

	if(logicAddr<CurAddr){
		printf("\tÌî³ä%d",(CurAddr - logicAddr));
	}

	logicAddr=CurAddr+CurMemberSize;
	printf("\n:%p ",CurAddr);
	printf("\t+%d",CurMemberSize);
///////////////////////////////////////////////////
	CurAddr=(unsigned long)(&((struct st_List *)0)->fouth);
	CurMemberSize=sizeof(*(struct st_List *)0).fouth;

	if(logicAddr<CurAddr){
		printf("\tÌî³ä%d",(CurAddr - logicAddr));
	}

	logicAddr=CurAddr+CurMemberSize;
	printf("\n:%p ",CurAddr);
	printf("\t+%d",CurMemberSize);
///////////////////////////////////////////////////
	CurAddr=(unsigned long)(&((struct st_List *)0)->fif);
	CurMemberSize=sizeof(*(struct st_List *)0).fif;

	if(logicAddr<CurAddr){
		printf("\tÌî³ä%d",(CurAddr - logicAddr));
	}

	logicAddr=CurAddr+CurMemberSize;
	printf("\n:%p ",CurAddr);
	printf("\t+%d",CurMemberSize);
/////////////////½áÊø//////////////////////////
	CurAddr=sizeof(*((struct st_List *)0));

	if(logicAddr<CurAddr){
		printf("\tÌî³ä%d",(CurAddr - logicAddr));
	}

	printf("\n:%p ",CurAddr);
	printf("\t½áÊø");
////////////////////////////////

#endif
	printf("\n");
}
