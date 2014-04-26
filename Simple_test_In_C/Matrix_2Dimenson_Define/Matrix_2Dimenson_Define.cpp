#include "iostream.h"
#include "math.h"

void main()
{
	
	int row=4;
	int col=3;
	int **A_val,**D_val;	
	A_val=new int*[row];
	D_val=new int*[row];
	int i,j;
	for(i=0;i<row;i++)
	{
		A_val[i]=new int[col];
		D_val[i]=new int[col];
		
	} 
	
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
		{
			A_val[i][j]=8;
			D_val[i][j]=10;
		cout<<A_val[i][j]<<"\n"<<D_val[i][j]<<endl;
		}
		cout<<i<<"  "<<j<<endl;
		
	
		
			
	for(int ii=0;ii<row;ii++) 
		{
			delete []A_val[ii]; 
			delete []D_val[ii];
		}
			delete []A_val; 
			delete []D_val;
			
			
			
}