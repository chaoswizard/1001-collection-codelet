#include <stdio.h>
#include <math.h>

void Int2Str(unsigned char str[],float var)
{
	float  num=(float)var; 
	int t=(int)num;
	int j=(int)((num-t)*100);
	int i,k;
	
	for(i=4;i>=0;i--)
   {
        k=(int)pow(10,i);
        str[4-i]=(unsigned char)((t/k)+48);
        t=t%k;
   }
    str[5]='.';
	str[6]=(unsigned char)((j/10)+48);
    str[7]=(unsigned char)((j%10)+48);
    str[8]='\0';
}
void main()
{
   int i=5;
   float var=(float)12345.568;
	while(i--)
	{unsigned char mystr[9];
	var+=0.01;
	Int2Str(mystr,var);
	printf("%s\n",mystr);
	}
}

