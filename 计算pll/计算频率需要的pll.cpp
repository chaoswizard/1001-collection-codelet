
/**
 * @FILE: 
 * @BRIEF: calc the pll val of freq.
 * @Copyright (C) 2011 .
 * @AUTHOR: WX
 * @DATE: 2011-03-06
 * @VERSION: 1.0
 * @REF:.
 */


#include "stdio.h"


typedef int T_S32;
typedef unsigned int T_U32;


/**
 * @BRIEF: ��min��max֮�������freqMhzΪ2^N��ϵ��pll��ֵ ��
 * @AUTHOR: WX
 * @DATE: 2011-03-06
 * @PARAM [in/out] T_S32 *pfreqMhz:the freq input,if need adjust,this will output the adjust val;
 * @PARAM [in]     T_S32 min:the  minimum of pll value sequence
 * @PARAM [in]     T_S32 max:the  maximum of pll value sequence
 * @RETURN T_S32:  the calc result
 * @RETVAL: -1:meaning failed. else meaning pll val.
 */
T_S32 calc_freq_matched_pll(T_S32 *pfreqMhz,T_S32 min,T_S32 max)
{
	T_S32 times = 0;
	T_S32 pll;
	T_S32 freqMhz = (*pfreqMhz);

	for (pll=min;pll<=max;pll++)
	{
		//���˷�������ϵ��ֵ.(��Ҫ�Ǽӿ�����,��ȷƥ��)
		if(freqMhz <= pll)
		{
			times = pll%freqMhz;
		}
		else 
		{
			times = freqMhz%pll;
		}
		
		if (times)
		{
			continue;
		}
		
		//���ʼ���
		if(freqMhz <= pll)
		{
			times = pll/freqMhz;
		}
		else 
		{
			times = freqMhz/pll;
		}

        //���ҵ�2��N�η����ʹ�ϵ������.add 03-07,use this line do judgement
		if ((0==times) || (times&(times-1)))
		{
			continue;
		}

		//del 03-07,need not this line to to judgetment
		/*�����������1�ĸ���
		tmp = times;
		count=0;
		while(tmp)
		{
			tmp &=(tmp-1);
			count++;
		}
		*/
		
		if(freqMhz <= pll)
		{
			(*pfreqMhz) = pll/times;
		}
		else
		{
			(*pfreqMhz) = times*pll;
		}
		return pll;
	}

	return -1;
}


/**
 * @BRIEF: ���� freq�� pllֵ;
 * @AUTHOR: WX
 * @DATE: 2011-03-06
 * @PARAM [in/out] T_S32 *pfreqMhz:the freq input,if need adjust,this will output the adjust val;
 * @PARAM [in]     T_U32 offsetMax:the max offset val of the adjust freq val; 
 * @RETURN T_S32:  the calc result
 * @RETVAL: -1:meaning failed. else meaning pll val.
 */
T_S32 get_pll(T_S32 *freq,T_U32 offsetMax)
{
	T_S32 freqMhz = (*freq);
	T_S32 pll;
	T_S32 offset = 0;
	T_S32 i=0;
	
	for (offset =0;offset<=offsetMax;offset++)
	{
		for (i=0;(offset>0)?(i<2):(i<1);i++)
		{
			if(0 == i)
			{
				//������������
				freqMhz = (*freq) + offset;
			}
			else if((*freq) > offset)
			{
				//������������
				freqMhz = (*freq) - offset;
			}
			else
			{
				break;
			}

			pll = calc_freq_matched_pll(&freqMhz,180,360);
			if(-1 != pll)
			{
				(*freq) = freqMhz;
				return pll;
			}
		}
		
	}
	
	return -1;
}


/**
 * @BRIEF: ���Ժ��� ����ӡmin��max֮������Ƶ�ʶ�Ӧ��pllֵ
 * @AUTHOR: WX
 * @DATE: 2011-03-06
 * @PARAM [in]     T_S32 min:the  minimum of freq val sequence
 * @PARAM [in]     T_S32 max:the  maximum of freq val sequence
 * @RETURN T_S32:  ret val
 */
T_S32 show_freq_pll(T_S32 min,T_S32 max)
{
	T_S32 freq,tmp,pll;
	T_S32 i=0;
	char lc,rc;
	T_S32 offset =0;
	
	
	for (freq = min;freq<max;freq++,i++)
	{
		tmp = freq;
		pll = get_pll(&tmp,7);
		
		offset = tmp - freq;
		if (0 == i%8)
		{
			printf("\n    ");
		}
		if (-1 == pll)
		{
			lc = '!';
			rc = '!';
		}
		else
		{
			if (pll == freq)
			{
				if (tmp == freq)
				{
					lc = '$';
					rc = '$';
				}
				else
				{
					lc = '#';
					rc = '#';
				}
			}
			else 
			{
				if (tmp == freq)
				{
					lc = '[';
					rc = ']';
				}
				else
				{
					lc = '%';
					rc = '%';
				}		
			}		
		}
		
		printf("%c%04d%+d=%04d=>%3d%c  ",lc,freq,offset,tmp,pll,rc);
		
	}
	printf("\n======================\n");
	
	
	return 0;
}


T_S32 main()
{
#define LEN_OFFSET  180
	T_S32 times = 10;
	T_S32 end =LEN_OFFSET;
	T_S32 begin = 1;
	
	while (times--)
	{
		show_freq_pll(begin,end);
		
		begin = end;
		end += LEN_OFFSET;	
	}
	
	return 0;
}


