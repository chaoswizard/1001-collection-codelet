#include <stdio.h>
#include <malloc.h>
#include <string.h>
int main(void)
{
	char * filePrefix="EPG";
    char *str;
    str= malloc(10);
    strcpy(str, "Hello");
    printf("String is %s  Address is %p\n", str, str);
    str = realloc(str, 20);
    printf("String is %s  New address is %p\n", str, str);

	printf("__len====%d\n",strlen(filePrefix));
    free(str);
    return 0;
}