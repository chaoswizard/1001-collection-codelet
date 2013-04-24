#include"iostream.h"
#include"iomanip.h"
int permutation(int m,int n)
{  int c=1;
for(n;n>=1;n--)c*=m--;
return c;
}
void display(int k)
{
	int x=1,m=1,n=1;
	
	
	for(n=1;n<k;n++)
	{   
		
		x=k*permutation(n,n);
		
		for(m=k;(m>n)&&(permutation(m,n)!=x);m--);
		if((m>n)&&(permutation(m,n)==x))
			cout<<setiosflags(ios::left)<<"m="<<setw(4)<<m<<"\tn="<<setw(4)<<n<<endl;
	}
}
void main()
{for(int k=2;k<=33;k++)//设置显示组数,大于35存在错误；
	{cout<<"\t   ----\n"<<"当组合值为  "<<k<<endl;cout<<"\t   ----"<<endl;
	  display(k);
	cout<<"==============="<<endl;}
}