#include "types.h"
#include "class_demoA.h"


typedef struct 
{
	uint32_t            m_a;
	uint32_t		    m_b;
} IDemoA;


DEFINE_CONSTRUCTOR_BEGIN(CDemoA)
{
	CDemoA *this = (CDemoA *)pthis;
	IDemoA *handle = NULL;

	handle = (IDemoA *)malloc(sizeof(IDemoA));
	if (NULL == handle) {
		printf("constructor error! out of memory!\n");
		return NULL;
	}
	printf("Constructor A\n");
	
	memset(handle, 0, sizeof(IDemoA));
	
	this->interface = (void *)handle;


	return this;
}
DEFINE_CONSTRUCTOR_END



DEFINE_DESTRUCTOR_BEGIN(CDemoA)
{
	CDemoA *this = (CDemoA *)pthis;
	IDemoA *handle = (IDemoA *)this->interface;

	printf("Destructor A\n");
	free(handle);
}
DEFINE_DESTRUCTOR_END



static int fun_a_implement(void *pthis)
{
	CDemoA *this = (CDemoA *)pthis;
	IDemoA *handle = (IDemoA *)this->interface;
		
	handle->m_a++;
	handle->m_b++;
	printf("Funa A\n");
	return handle->m_a;
}

static int fun_b_implement(void *pthis, char *a, int b)
{
	CDemoA *this = (CDemoA *)pthis;
	IDemoA *handle = (IDemoA *)this->interface;
		
	handle->m_b = b;
	
	printf("Funb(%s,%d) A\n", a, b);
	return handle->m_b;
}

REGISTER_FUNC_BEGIN(CDemoA, CONSTRUCTOR_FUNC(CDemoA), DESTRUCTOR_FUNC(CDemoA))
REGISTER_FUNC(fun_a, fun_a_implement)
REGISTER_FUNC(fun_b, fun_b_implement)
REGISTER_FUNC_END(CDemoA)

REGISTER_CLASS_C(CDemoA)

