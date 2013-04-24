#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef	unsigned char           T_U8;		/* unsigned 8 bit integer */
typedef	 char           T_S8;		/* unsigned 8 bit integer */
typedef	unsigned int			T_U32,T_BOOL;		/* unsigned 32 bit integer */
typedef	signed int 			T_S32;		/* signed 32 bit integer */
typedef void                 T_VOID;
#define AK_FALSE  0
#define AK_TRUE   1
#define AK_NULL   NULL


static T_VOID U64_Add_Dump(T_S8 *tips, T_U8 *valBuf, T_U8 msb)
{
	T_U8 strbuf[22];
	T_U8 i =0;
	
	memset(strbuf,0,22);

	for (i=0;i<msb;i++)
	{
		strbuf[i] = valBuf[msb-1-i] + '0';
	}
	printf("%s%015s \n",tips,strbuf);
}



#if 0
/**
    * @BRIEF    long  integer add
    * @AUTHOR  wang xi
    * @DATE     2010-10-28
    * @PARAM    sumBuf   -  a long integer buffer and for restory the sum . 
    *                   augendBuf   -  a long integer buffer  for add  to sumBuf
    *                   msb      -  most hight bit
    *                   base     -  mathematic base number(must between 2 and 255)
    * @RETURN  T_S32
    * @RETVAL   the msb of sum
*/
T_S32 LongInt_Add(T_U8 *sumBuf,const T_U8 *augendBuf,T_S32 msb,T_U8 base)
{
	T_S32 i = 0 , tmpVal = 0;
	T_S32 mostHighBit = msb;
	T_BOOL bExistCarry = AK_FALSE;
	
	for (i=0;i<mostHighBit;i++)
	{
		sumBuf[i] = sumBuf[i] + augendBuf[i];
	}
	
	do
	{
		bExistCarry = AK_FALSE;
		for (i=0;i<mostHighBit;i++)
		{
			tmpVal = sumBuf[i];
			
			if (tmpVal >= base)
			{
				bExistCarry = AK_TRUE;
				sumBuf[i] = tmpVal%base;
				sumBuf[i+1] = sumBuf[i+1] + tmpVal/base;
				if (mostHighBit < (i+2))
				{
					mostHighBit = (i+2);
				}
			}
		}
	} while(bExistCarry);
	
	return mostHighBit;
}



/**
    * @BRIEF    64 bit  integer tanslate to Ascii string
    * @AUTHOR  wang xi
    * @DATE     2010-10-28
    * @PARAM    high  /low -  64 bit integer high 32 bit  and low 32 bit
    *                   srcBuf   - restore the translate result
    * @RETURN  T_S32
    * @RETVAL   0 - translate successful
    * @RETVAL   other  - Failed
*/

T_S32 U64_Int2Str(T_U32 high, T_U32 low, T_U8 *strBuf)
{
	T_U8 val1[22] = {0}; 
	T_U8 val2[22] = {0}; 
	T_U8 i=0;
	T_U32 tmpVal = 0;
	T_U32 length = 0;
	T_U8 mostBit = 0;
	
	if (AK_NULL == strBuf)
	{
		return -1;
	}

	memset(val1,0,sizeof(val1));
	if (high > 0)
	{
		memset(val2,0,sizeof(val2));
	// "4294967296" 2^32
		val2[0] = 6;val2[1] = 9;val2[2] = 2;val2[3] = 7;val2[4] = 6;
		val2[5] = 9;val2[6] = 4;val2[7] = 9;val2[8] = 2;val2[9] = 4;
		mostBit = 10;
		length = high;
		while(length--)
		{
			U64_Add_Dump("+",val2,10);
			mostBit = LongInt_Add(val1,val2,mostBit,10);
			U64_Add_Dump("=",val1,mostBit);
		}
	}
	

	tmpVal = low;
	i = 0;
	memset(val2,0,sizeof(val2));
	while(tmpVal>=10)
	{
		val2[i] = tmpVal%10;
		tmpVal = tmpVal/10;
		i++;
	}
	val2[i] = tmpVal;
	U64_Add_Dump("*",val2,i+1);
	if (mostBit < (i+1))
	{
		mostBit = i+1;
	}
	mostBit = LongInt_Add(val1,val2,mostBit,10);
	U64_Add_Dump("=",val1,mostBit);

	for (i=0;i<mostBit;i++)
	{
		strBuf[i] = val1[mostBit-1-i] + '0';
	}
	return 0;
}
#endif

/**
    * @BRIEF    long  integer add
    * @AUTHOR  wang xi
    * @DATE     2010-10-28
    * @PARAM    sumBuf   -  a long integer buffer and for restory the sum . 
    *                   augendBuf   -  a long integer buffer  for add  to sumBuf
    *                   msb      -  most hight bit
    *                   base     -  mathematic base number(must between 2 and 255)
    * @RETURN  T_S32
    * @RETVAL   the msb of sum
*/
T_S32 LongInt_Add(T_U8 *sumBuf,const T_U8 *augendBuf,T_S32 msb,T_U8 base)
{
	T_S32 i = 0 , tmpVal = 0;
	T_S32 mostHighBit = msb;
	T_BOOL bExistCarry = AK_FALSE;
	
	for (i=0;i<mostHighBit;i++)
	{
		sumBuf[i] = sumBuf[i] + augendBuf[i];
	}
	
	do
	{
		bExistCarry = AK_FALSE;
		for (i=0;i<mostHighBit;i++)
		{
			tmpVal = sumBuf[i];
			
			if (tmpVal >= base)
			{
				bExistCarry = AK_TRUE;
				sumBuf[i] = tmpVal%base;
				sumBuf[i+1] = sumBuf[i+1] + tmpVal/base;
				if (mostHighBit < (i+2))
				{
					mostHighBit = (i+2);
				}
			}
		}
	} while(bExistCarry);
	
	return mostHighBit;
}



/**
    * @BRIEF    64 bit  integer tanslate to Ascii string(base number is 10)
    * @AUTHOR  wang xi
    * @DATE     2010-10-28
    * @PARAM    high  /low -  value of 64 bit integer high / low 32 bit
    *                   strBuf   - restore the translate result
    * @RETURN  T_S32
    * @RETVAL   0 - translate successful
    * @RETVAL   other  - Failed
*/
T_S32 U64_Int2Str(T_S8 *strBuf,T_U32 high , T_U32 low)
{
	T_U8 sumbuf[22] = {0}; 
	T_U8 augendbuf[22] = {0}; 
	T_U8 i=0;
	T_U32 tmpVal = 0;
	T_U32 length = 0;
	T_U8 mostBit = 0;
	
	if (AK_NULL == strBuf)
	{
		return -1;
	}

	memset(sumbuf,0,sizeof(sumbuf));
	if (high > 0)
	{
		memset(augendbuf,0,sizeof(augendbuf));
	// "4294967296" 2^32
		augendbuf[0] = 6;augendbuf[1] = 9;augendbuf[2] = 2;augendbuf[3] = 7;augendbuf[4] = 6;
		augendbuf[5] = 9;augendbuf[6] = 4;augendbuf[7] = 9;augendbuf[8] = 2;augendbuf[9] = 4;
		mostBit = 10;
		length = high;
		while(length--)
		{
			mostBit = (T_U8)LongInt_Add(sumbuf,augendbuf,mostBit,10);
		}
	}
	
	tmpVal = low;
	i = 0;
	memset(augendbuf,0,sizeof(augendbuf));

	while (tmpVal >= 10)
	{
		augendbuf[i] = (T_U8)(tmpVal%10);
		tmpVal = tmpVal/10;
		i++;
	}
	
	augendbuf[i] = (T_U8)tmpVal;

	if (mostBit < (i+1))
	{
		mostBit = i+1;
	}
	mostBit = (T_U8)LongInt_Add(sumbuf,augendbuf,mostBit,10);

	for (i=0;i<mostBit;i++)
	{
		strBuf[i] = sumbuf[mostBit-1-i] + '0';
	}
	return 0;
}

#define MAX_STR_LEN  100






int main()
{
	T_S8 val1[MAX_STR_LEN] = {0}; 

	memset(val1,0,sizeof(val1));
	U64_Int2Str(val1,0,0);
	printf("%s\n",val1);
     
	return 0;
}
