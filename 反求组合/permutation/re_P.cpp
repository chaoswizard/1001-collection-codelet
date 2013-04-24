#include"iostream.h"
#include"iomanip.h"
int permutation(int m,int n)
{  int c=1;
  for(n;n>=1;n--)c*=m--;
  return c;
}
void main()
{
  int k,x=1,m=1,n=1;
  cout<<"请输入组合结果"<<endl;
  cin>>k;//k 大于35后存在错误；
  
	for(n=1;n<k;n++)
	{   
		x=k*permutation(n,n);
		for(m=k;(m>n)&&(permutation(m,n)!=x);m--);
		if((m>n)&&(permutation(m,n)==x))
		cout<<setiosflags(ios::left)<<"m="<<setw(4)<<m<<"\tn="<<setw(4)<<n<<endl;
	}
 
}