#include    <stdio.h>
#include <conio.h>
void    main()
{
    char flower[] = {'\\','|','/','*'};
    char c;
    unsigned int count=0,flag=1;
    long unsigned int delay;

    while(1)
    {   while(flag)

	{
	    printf("%c\b",flower[count++%4]);
	    delay=65552225;
	    do{;}while(delay--);
	    if(kbhit())flag=0;

	}
	 c=getch();
	 flag=1;
	if(c=='q')
	{
	    printf("\n over \n");
	    delay=65522200;
	    do{;}while(delay--);
	   return;
        }
    }

}
