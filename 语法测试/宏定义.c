#include "stdio.h"

#define printf

int test_fun()
{
	putchar('A');

	return 0;
}


int main()
{
	//��ʾA�� ������û����ʾ
	printf("Test: %d\n", test_fun());
	return 0;
}