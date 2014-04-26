#include "stdio.h"
#include "test_define.h"

	


struct st_List{
	char first;//4
	short second;//2
	char third;//1
	long fouth;//4
	char fifth;//1
};





void main()
{

	unsigned long pad_cnt = 0;

	struct_pad_dump(struct st_List, first, offsetof(struct st_List, second), pad_cnt);
	struct_pad_dump(struct st_List, second, offsetof(struct st_List, third), pad_cnt);
	struct_pad_dump(struct st_List, third, offsetof(struct st_List, fouth), pad_cnt);
	struct_pad_dump(struct st_List, fouth, offsetof(struct st_List, fifth), pad_cnt);
	struct_pad_dump(struct st_List, fifth, sizeof(struct st_List), pad_cnt);
}
