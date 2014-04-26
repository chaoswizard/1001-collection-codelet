#include <stdio.h>
#include <math.h>
#include <iostream.h>
#include<string.h>
typedef signed int  int32;
//在处理浮点运算时，一定要先乘加后减除，最好全部化为乘加运算。
unsigned char mystr[9];
void Int2Str(unsigned char str[],double var)
{
	if(var<1) 
	{
	int i;
	int32 j=(int32)(var*100);
	for(i=0;i<=4;i++)
	str[i]='0';
	str[5]='.';
	str[6]=(unsigned char)((j/10)+48);
	str[7]=(unsigned char)((j%10)+48);
	str[8]='\0';
	}
	
	else 
	{
		//cout<<"int2str========="<<var<<endl;
		int32 t=(int32)var;
		int32 j=(int32)((int32)(var*100)-(int32)(t*100));
		int i,k;
		//cout<<"int2str++++++++++"<<t<<endl;
		for(i=4;i>=0;i--)
  		 {
       		 k=(int32)pow(10,i);
       		 str[4-i]=(unsigned char)((t/k)+48);
			 t=t%k;
		 }
		str[5]='.';
		str[6]=(unsigned char)((j/10)+48);
		str[7]=(unsigned char)((j%10)+48);
		str[8]='\0';
    }
}
void main()
{
	cout<<"char-->"<<sizeof(char)<<endl;
	cout<<"signed char-->"<<sizeof(signed char)<<endl;
	cout<<"unsigned char-->"<<sizeof(unsigned char)<<endl;
	cout<<"int-->"<<sizeof(int)<<endl;
	cout<<"signed int-->"<<sizeof(signed int)<<endl;
	cout<<"unsigned int-->"<<sizeof(unsigned int)<<endl;
	cout<<"signed short-->"<<sizeof(signed short)<<endl;
	cout<<"unsigned short-->"<<sizeof(unsigned short)<<endl;
	cout<<"float-->"<<sizeof(float)<<endl;
	cout<<"double-->"<<sizeof(double)<<endl;
	cout<<"=============================================="<<endl;

    signed int i=1,k=1;
    double keysum=12345.348965;
	while(i--)
	{
	Int2Str(mystr,keysum);
	printf("%s -->   %lf\n",mystr,keysum);
	keysum=keysum*10+k++;
	
	//var=float((var*100+10)/100);//即var自增0.1,此处为优化处理
	}
    double test=123456.34;
	cout<<"test"<<endl;
	cout<<int32(test)<<endl;
	
}

