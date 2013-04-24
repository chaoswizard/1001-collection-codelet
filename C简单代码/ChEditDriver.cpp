#include "stdio.h"


#include "malloc.h"

typedef struct{
	int chNum;
	int freq;
}EDITITEMDATA;

typedef struct ONEEDITITEM{
	EDITITEMDATA data;
	struct ONEEDITITEM *next;
}EDITITEM,*EDITITEMLIST;
static EDITITEMLIST delList=NULL;
static EDITITEMLIST skipList=NULL;



static EDITITEMLIST  InitOneEditList(int a,int b)
{
	EDITITEMLIST list=NULL;
	list=(EDITITEMLIST)malloc(sizeof(EDITITEM));
	if(NULL==list){
		printf("\nCreate failed\n");
		return NULL;
	}
	list->next=NULL;
	list->data.chNum=a;
	list->data.freq=b;

	printf("\nCreate %d Ok\n",a);
	return list;
}

static void FreeOneList(EDITITEMLIST *list)
{
	EDITITEMLIST head;
	while((*list)!=NULL){
		head=(*list);
		(*list)=(*list)->next;
		free(head);
		head=NULL;
	}
}
static bool KvEdit_InitOneEditList(EDITITEMLIST *list)
{
	(*list)=InitOneEditList(0,0);
	if(NULL==(*list)){
		return false;
	}else{
		return true;
	}
}


static bool  reActionOneEdititem(EDITITEMLIST *list,int a,int b)
{
	EDITITEMLIST head,tmp;
	bool isFind=false;
	if(NULL==(*list)){
		return false;
	}
	tmp=head=(*list);
	(*list)=(*list)->next;//
	while((*list)!=NULL){
		isFind=false;
		printf("\n--check--%d++is+++%d\n",(*list)->data.chNum,(*list)->data.freq);
		if(((*list)->data.chNum==a)&&((*list)->data.freq==b)){
			isFind=true;
			printf("\nsearched!\n");
			break;
		}
		tmp=(*list);
		(*list)=(*list)->next;
	}

	if(isFind){
		printf("\ndelete this node!\n");
		if(NULL!=(*list)){
			tmp->next=(*list)->next;
			free((*list));
			(*list)=NULL;
		}
		(*list)=head;
		return true;
	}else{
		printf("\ncan not searched\n");
		printf("\nadd this node!\n");
		tmp->next=InitOneEditList(a,b);
		(*list)=head;
		return true;
	}

	return false;
}

static bool  KvEdit_SearchOneEditList(EDITITEMLIST list,int a,int b)
{
	EDITITEMLIST tmp;

	tmp=list->next;//
	while(tmp!=NULL){
		if((tmp->data.chNum==a)&&(tmp->data.freq==b)){
			return true;
		}
		tmp=tmp->next;
	}
	return false;
}

int KvEdit_getOneListLength(EDITITEMLIST list)
{
	EDITITEMLIST tmp;
	int len=0;
	if(NULL==list)
		return -1;

	tmp=list->next;//
	while(tmp!=NULL){
		len++;
		tmp=tmp->next;
	}
	return len;
}

//比较oldList是否和newList相同(含有相同的Node)
static bool KvEdit_CompareTwoList(EDITITEMLIST oldList,EDITITEMLIST newList)
{
	int len1=-1,len2=-1;
	EDITITEMLIST tmp;
	bool isSame;
	len1=KvEdit_getOneListLength(oldList);
	len2=KvEdit_getOneListLength(newList);
	if(len1!=len2){
		printf("\n\t\t-->len not same!\n");
		return false;
	}

	if(-1==len1){//空表
		printf("\n\t\t-->empty list!\n");
		return true;
	}
	tmp=oldList->next;//

	isSame=true;
	while(tmp!=NULL){
		if(KvEdit_SearchOneEditList(newList,tmp->data.chNum,tmp->data.freq)){
			 isSame=true;
		}else{
			isSame=false;
			break;
		}
		tmp=tmp->next;
	}
	return isSame;
}

static void PrintfCmpResult(EDITITEMLIST delList,EDITITEMLIST skipList)
{
	if(KvEdit_CompareTwoList(delList,skipList)){
		printf("\n\t\t\t**** same *************\n");
	}else{
		printf("\n\t\t\t***** not same***\n");
	}

}

 void main()
 {
	 EDITITEMLIST tmp=NULL;
	 KvEdit_InitOneEditList(&delList);
	 KvEdit_InitOneEditList(&skipList);

	PrintfCmpResult(delList,skipList);//////

	reActionOneEdititem(&delList,1,999);

	PrintfCmpResult(delList,skipList);//////
	reActionOneEdititem(&skipList,1,999);
	PrintfCmpResult(delList,skipList);//////

	reActionOneEdititem(&delList,2,999);
	reActionOneEdititem(&delList,3,999);
	reActionOneEdititem(&delList,4,999);

	FreeOneList(&delList);
	 if(NULL==delList){
		printf("\nFree OK\n");
	 }else{
		printf("\n Failed \n");
	 }
 }