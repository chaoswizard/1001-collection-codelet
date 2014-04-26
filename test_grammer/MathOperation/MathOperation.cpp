#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void test_sub_c()
{
	int i = 3;

	printf("sub_c:begin %d\n",i);

	do {
		printf("%d\n", i-=1);
	} while(!(--i));
	
	printf("sub_c:end %d\n",i);
}



void test_sub_b()
{
	int i = 3;

	printf("sub_b:begin %d\n",i);

	do {
		printf("%d\n", i--);
	} while(!(--i));
	
	printf("sub_b:end %d\n",i);
}


void test_sub_a()
{
	int i = 3;
	
	printf("sub_a:begin %d\n", i);

	do {
		printf("%d\n", i-=2);
	} while(!(--i));

	printf("sub_a:end %d\n", i);
}

int main()
{
	test_sub_a();
	printf("\n===\n");
	test_sub_b();
	printf("\n===\n");
	test_sub_c();
}


