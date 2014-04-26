#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc,char**argv)
{
	char *filename = NULL,*keystr = NULL;
	FILE *fp = NULL;
	char *headbuf = NULL;
	int i = 0,j=0,z =0,headlen = 0,keylen = 0,blkcnt=0;

	printf(" %0x\n",argc);
	printf(" %s\n",argv[0]);

	if (NULL != (filename = argv[1]))
	{
		printf("File is %s.\n",filename);
	}
	else
	{
	    printf("no file input!\n");
		return 0;
	}

	if (NULL !=  argv[2])
	{
		headlen = atoi(argv[2]);
		if (headlen <= 0)
		{
			printf("headlen is invalid!\n");
			return 0;
		}
		printf("File Head len is %d Byte%s.\n",headlen,(headlen>1)?"s":"");
	}
	else
	{
	    printf("no headlen input!\n");
		return 0;
	}
	
    if (NULL == argv[3])
	{
	    printf("no key input!\n");
		return 0;
	}
	else
	{
		keystr = argv[3];
		keylen = strlen(keystr);
	}

	if ((keylen <= 0) || (headlen < keylen) || 0!=(headlen%keylen))
	{
	    printf("key is invalid<keylen=%d>!\n",keylen);
		return 0;
	}
	else
	{
	    printf("key is [%s].<len = %d>\n",keystr,keylen);
	}

	fp = fopen(filename,"rb+");
	if (NULL == fp)
	{
		printf(" Open file error!\n");
		return 0;
	}

	headbuf = (char*)malloc(headlen+2);

	if (NULL == headbuf)
	{
		fclose(fp);
		printf("Malloc  error!\n");
		return 0;
	}

	fseek(fp,0,SEEK_SET);
	i = fread(headbuf,1,headlen,fp);
	if (headlen != i)
	{
		fclose(fp);
		free(headbuf);
		printf("fread  error <read %d of %d>!\n",i,headlen);
		return 0;
	}

	blkcnt = headlen/keylen;
	for (i=0;i< blkcnt;i++)
	{
		z = keylen*i;
		for (j=0;j<keylen;j++)
		{
			headbuf[z+j] = headbuf[z+j]^keystr[j];
		}
	}
	fseek(fp,0,SEEK_SET);
	if (headlen != fwrite(headbuf,1,headlen,fp))
	{
		printf("write  error!\n");
	}
	else
	{
		printf("successful!\n");
	}
	free(headbuf);
	fclose(fp);
	return 0;
}