#include "stdio.h"



int g_test_val = 5;


int test_fun()
{
	return g_test_val--;	
}


int main()
{
	//���ҵ���
	printf("Test: %d, %d, %d\n", g_test_val, test_fun(), g_test_val);
	return 0;
}
