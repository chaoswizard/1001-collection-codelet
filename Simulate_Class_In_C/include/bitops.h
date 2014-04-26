#ifndef _ANYKA_BITOPS_H
#define _ANYKA_BITOPS_H

#include "compiler.h"

#define BITS_PER_LONG 32

#define BIT(nr)			(1UL << (nr))
#if 0
#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)
#define BITS_PER_BYTE		8

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static __inline__ int test_bit(int nr, const volatile unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}
static __inline__ void set_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

	*p  |= mask;
}

static __inline__ void clear_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

	*p &= ~mask;
}
#else

#define test_bit(nr, addr) (1UL & (((unsigned long *)addr)[0] >> (nr & (31))))
#define set_bit(nr, addr)  (((unsigned long *)addr)[0] |= BIT(nr & (31)))
#define clear_bit(nr, addr) (((unsigned long *)addr)[0] &= (~ (BIT(nr & (31)))))
#endif
#endif

