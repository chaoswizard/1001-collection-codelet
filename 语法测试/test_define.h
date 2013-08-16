
#ifndef __TEST_MACRO_DEFINE_H__
#define __TEST_MACRO_DEFINE_H__


#define offsetof(type, member)  ((unsigned long)(&((type *)0)->member))

#define member_entry(ptr, type, member)	\
	((unsigned long)((char *)(ptr)+ offsetof(type, member))

#define member_size(type, member)	(sizeof((type *)0)->member)


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

#endif