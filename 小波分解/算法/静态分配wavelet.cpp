#include "iostream.h"
#include "math.h"
#define    ROW_MAX   8
#define    COL_MAX   128

double REFVAL=pow(2,0.5);//

double set_A(double a,double b)
{return (a+b)/REFVAL;}

double set_D(double a,double b)
{return (a-b)/REFVAL;}
/////////////////////////////////////////////////////////////////////////////////
void Inverse_DWT(double Src_val[],double C_val[],int n_total,int levl)
{
		int row; 
		int col;
		double A_val[ROW_MAX+1][COL_MAX];
		double D_val[ROW_MAX+1][COL_MAX];
		int len=(int)(n_total/pow(2,levl));
		int init;
		for(init=0;init<len;init++)//initialize the matrix,fill all the D_matrix and Ak row;
			A_val[levl][init]=C_val[init];
		for(row=levl;row>=1;row--)
		{
		len=(int)(n_total/pow(2,row));
		for(col=0;col<len;col++)
			D_val[row][col]=C_val[init++];
		}
		//Haar Inverse DWT Process
		for(row=levl;row>=2;row--)//row-1=1,so row=2;
		{
		len=(int)(n_total/pow(2,row));
		for(col=0;col<len;col++)
			{
			A_val[row-1][2*col]  =set_A(A_val[row][col],D_val[row][col]);
			A_val[row-1][2*col+1]=set_D(A_val[row][col],D_val[row][col]);
			}
		}

		//load  the result from the A matrix and D matrix to C matrix;
		for(col=0;col<(int)(n_total/2);col++)
		{
		Src_val[2*col]=set_A(A_val[1][col],D_val[1][col]);
		Src_val[2*col+1]=set_D(A_val[1][col],D_val[1][col]);
		}
		cout<<"解码结果"<<endl;////////////////////////////this is a test print
		for(int x=0;x<n_total;x++)
			cout<<"\t"<<Src_val[x]<<endl;

	
	}

///////////////////////////////////////////////////////////////////////////////////////////
void haar_DWT(double Src_val[],double C_val[],int n_total,int levl)
{
		int row; 
		int col=n_total/2;
		double A_val[ROW_MAX+1][COL_MAX];
		double D_val[ROW_MAX+1][COL_MAX];
		for(int init=0;init<col;init++)//initialize the matrix,as the 1 level encode,this length is half of the n_total;
		{
		A_val[1][init]=set_A(Src_val[2*init],Src_val[2*init+1]);
		D_val[1][init]=set_D(Src_val[2*init],Src_val[2*init+1]);
		}
		int N=n_total/2;
		row=2;
		for(row=2;row<=levl;row++)//DWT,the level row will been filled;
		{	
			N=N/2;
			for(col=0;col<N;col++)
			{
				A_val[row][col]=set_A(A_val[row-1][2*col],A_val[row-1][2*col+1]);
				D_val[row][col]=set_D(A_val[row-1][2*col],A_val[row-1][2*col+1]);
			}
		}
		//load  the result from the A matrix and D matrix to C matrix;
		int len=(int)(n_total/pow(2,levl));//length for the ENcode level;
		int cindex=0;
		for(cindex=0;cindex<len;cindex++)//load the Ak from the A matrix's level row;
			C_val[cindex]=A_val[levl][cindex];
	
		for(row=levl;row>=1;row-- )
		{
			len=(int)(n_total/pow(2,row));
			for(col=0;col<len;col++)//load all the Dk from the D matrix;
				C_val[cindex++]=D_val[row][col];
		}
		cout<<"编码结果"<<endl;////////////////////////////this is a test print
		for(int x=0;x<n_total;x++)
			cout<<"\t"<<C_val[x]<<endl;
	}
void main()
{	double Src_val[2*ROW_MAX]={2,3,4,6,2,3,4,6},C_val[2*ROW_MAX];
	

	int flag=0;
	int levl=3;//ENcode level
	int n_total=8;
	cout<<"初始数据:\n";
	for(int i=0;i<n_total;i++)
		cout<<"\t"<<Src_val[i]<<endl;
	haar_DWT(Src_val,C_val,n_total,levl);
	Inverse_DWT(Src_val,C_val,n_total,levl);
	
}
