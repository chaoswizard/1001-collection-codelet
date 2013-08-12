#ifndef _ELVON_TYPES_H
#define _ELVON_TYPES_H

#include "asm_types.h"
#include "posix_types.h"

/*
 * The following typedefs are also protected by individual ifdefs for
 * historical reasons:
 */
#if 0//ndef _SIZE_T
#define _SIZE_T
typedef __kernel_size_t		size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef __kernel_ssize_t	ssize_t;
#endif




#ifndef _STRUCT_TIMESPEC
#define _STRUCT_TIMESPEC
struct timespec {
	__kernel_time_t	tv_sec;			/* seconds */
	long		tv_nsec;		/* nanoseconds */
};
#endif

#define __bitwise__ 
#if 0//def __CHECK_ENDIAN__
#define __bitwise __bitwise__
#else
#define __bitwise
#endif


/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

//typedef		__u8		u_int8_t;
typedef		__s8		int8_t;
//typedef		__u16		u_int16_t;
typedef		__s16		int16_t;
//typedef		__u32		u_int32_t;
typedef		__s32		int32_t;

#endif /* !(__BIT_TYPES_DEFINED__) */

typedef		__u8		uint8_t;
typedef		__u16		uint16_t;
typedef		__u32		uint32_t;



#define TRUE  1
#define FALSE 0
//#define boolean uint8_t
typedef		uint8_t		boolean;

typedef unsigned __bitwise__ gfp_t;

#ifndef NULL
#define NULL  0
#endif

typedef u32 phys_addr_t;
typedef u32 dma_addr_t;


typedef phys_addr_t resource_size_t;

typedef struct {
	volatile int counter;
} atomic_t;

#endif
