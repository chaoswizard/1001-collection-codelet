#include "stdio.h"


#define offsetof(type, member)  ((unsigned long)(&((type *)0)->member))

#define member_entry(ptr, type, member)	\
	((unsigned long)((char *)(ptr)+ offsetof(type, member))

#define member_size(type, member)	(sizeof((type *)0)->member)
	


struct st_List{
	char first;//4
	short second;//2
	char third;//1
	long fouth;//4
	char fifth;//1
};

#define struct_pad_dump(type_name, cur_member, next_ofs, pad_count) do {\
	unsigned int cur_ofs = offsetof(type_name, cur_member);\
	unsigned int cur_size = member_size(type_name, cur_member);\
	unsigned int cur_tail = offsetof(type_name, cur_member) + member_size(type_name, cur_member);\
	if(next_ofs > cur_tail){\
		unsigned int pad_size = (next_ofs - cur_tail);\
		pad_count+= pad_size;\
		printf("[%d]%s\t:%08X Моід%d -> %08X\n", cur_size, #cur_member, cur_ofs, pad_size, next_ofs);\
	} else {\
		printf("[%d]%s\t:%08X\n", cur_size, #cur_member, cur_ofs);\
	}\
} while(0)




void main()
{
#if 0
	st_List mylist;

	printf("\n:%p ",member_entry(&mylist,struct st_List,fouth));
	printf("\n:%p ",&(mylist.fouth));

#else
	unsigned long pad_cnt = 0;

	struct_pad_dump(struct st_List, first, offsetof(struct st_List, second), pad_cnt);
	struct_pad_dump(struct st_List, second, offsetof(struct st_List, third), pad_cnt);
	struct_pad_dump(struct st_List, third, offsetof(struct st_List, fouth), pad_cnt);
	struct_pad_dump(struct st_List, fouth, offsetof(struct st_List, fifth), pad_cnt);
	struct_pad_dump(struct st_List, fifth, sizeof(struct st_List), pad_cnt);

////////////////////////////////

#endif
	printf("\n");
}
