#include "stdio.h"

#define printf

int test_fun()
{
	putchar('A');

	return 0;
}


int main()
{
	//显示A， 而不是没有显示
	printf("Test: %d\n", test_fun());
	return 0;
}