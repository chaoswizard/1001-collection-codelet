#include <stdio.h>



void main()
{
	int a=0x00070001;
	int b=0x000007ff;
    int c=a|b;
	printf("%08X | %08X = %08x \n",a, b, c);
	

}