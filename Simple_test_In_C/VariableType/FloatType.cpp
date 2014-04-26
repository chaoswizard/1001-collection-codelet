#include<iostream.h>
void main()
{
	//short int i=5,k=5,j=5;
//	cout<<sizeof(short int)<<endl;
//	while(k--)
//	{	cout<<i<<endl;i=!i;}
//	i=j;
//	cout<<"endl>>>> "<<i<<endl;

	double i=-1.01;
	signed int j;
	unsigned int k;
	int l;
	l=(int)i;
	k=(unsigned int)i;
	j=(signed int)i;
	cout<<"double is :"<<i<<endl;
	cout<<"int\t     "<<l<<"\nunsigned int "<<k<<"\n  signed int "<<j<<endl;

	double ii=55555.453,jj=55555.875;
	cout<<(int)(ii*10)<<"\n"<<(int)(jj*10)<<endl;

}