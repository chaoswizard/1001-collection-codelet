#include <stdio.h>

struct st_bittype_a{
	struct {
		int a:6;
		int b:4;
		int c:1;
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

#define debug_size(__var)  printf("size " #__var " %d\n",sizeof(__var))

void test_struct_size()
{
	struct st_bittype_a a;
	struct st_bittype_b b;
	
	debug_size(short);
	debug_size(a);
	debug_size(a.test);
	//debug_size(a.e);
	//printf("\nsss:%d\n", sizeof(a.e));
	debug_size(b);
	//debug_size(b.e);
}

void main()
{
	int a=0x00070001;
	int b=0x000007ff;
    int c=a|b;
	printf("%08X | %08X = %08x \n",a, b, c);
	
	test_struct_size();
}