#include <stdio.h>

struct st_bittype_a{
	struct {
		int a:6;
		int b:4;
		int c:4;
		int d:3;
	} test;
		int e:1;
};

struct st_bittype_b{
		int a:6;
		int b:4;
		int c:4;
		int d:3;
		int e:1;
};



void main()
{
	int a=0x00070001;
	int b=0x000007ff;
    int c=a|b;
	printf("%08X | %08X = %08x \n",a, b, c);
	
	printf("struct_size:%d,%d\n", sizeof(st_bittype_a), sizeof(st_bittype_b));

}