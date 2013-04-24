
#include <iostream.h>


void main (void)
{
	int keycode = 0xff;
	int row;
	int col;
	for(col=0;col<4;col++)
	{
		
		for(row=0;row<4;row++)
		{
			keycode = row*10+col;	
			cout<<keycode<<endl;
			
		}

	}
	
	
}