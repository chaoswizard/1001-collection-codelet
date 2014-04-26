
#include "types.h"
#include "class_demoA.h"
#include "class_demoB.h"

// interface
typedef struct
{
	uint32_t		    m_a;
	uint32_t		    m_b;
	CDemoA             *m_ClsA1;
	CDemoA             *m_ClsA2;
} IDemoB;


DEFINE_CONSTRUCTOR_BEGIN(CDemoB)
{
	CDemoB *this = (CDemoB *)pthis;
	IDemoB *handle = NULL;

	handle = (IDemoB *)malloc(sizeof(IDemoB));
	if ( NULL == handle ) {
		printf("constructor error! out of memory!\n");
		return NULL;
	}
	
	printf("Construct B\n");

	memset(handle, 0, sizeof(IDemoB));
	
	this->interface = (void *)handle;
	handle->m_ClsA1 = NEW_CLASS(CDemoA);
	if (NULL == handle->m_ClsA1) {
		printf("constructor child cls1 error!\n");
		return NULL;
	}

	handle->m_ClsA2 = NEW_CLASS(CDemoA);
	if (NULL == handle->m_ClsA2) {
		printf("constructor child cls2 error!\n");
		return NULL;
	}
	
	return this;
}
DEFINE_CONSTRUCTOR_END



DEFINE_DESTRUCTOR_BEGIN(CDemoB)
{
	CDemoB *this = (CDemoB *)pthis;
	IDemoB *handle = (IDemoB *)this->interface;

	if (NULL != handle->m_ClsA2) {
		DEL_CLASS(CDemoA, handle->m_ClsA2);
		handle->m_ClsA2 = NULL;
	}

	if (NULL != handle->m_ClsA1) {
		DEL_CLASS(CDemoA, handle->m_ClsA1);
		handle->m_ClsA1 = NULL;
	}

	printf("Destruct B\n");
	
	free(handle);
}
DEFINE_DESTRUCTOR_END

static int funa_implement(void *pthis)
{
	CDemoB *this = (CDemoB *)pthis;
	IDemoB *handle = (IDemoB *)this->interface;
		
	handle->m_a = CLASS_FUNC_0P(CDemoA, handle->m_ClsA1, fun_a);
	handle->m_b = CLASS_FUNC_0P(CDemoA, handle->m_ClsA2, fun_a);
	
	printf("Funa B\n");
	return handle->m_b;
}


static int funb_implement(void *pthis, char* a, int b)
{
	CDemoB *this = (CDemoB *)pthis;
	IDemoB *handle = (IDemoB *)this->interface;
		
	handle->m_a = b + CLASS_FUNC_2P(CDemoA, handle->m_ClsA1, fun_b, a, handle->m_a);
	handle->m_b = b + CLASS_FUNC_2P(CDemoA, handle->m_ClsA2, fun_b, a, handle->m_b);

	printf("Funb(%s,%d) B\n", a, b);

	return handle->m_b;
}

REGISTER_FUNC_BEGIN(CDemoB, CONSTRUCTOR_FUNC(CDemoB), DESTRUCTOR_FUNC(CDemoB))
REGISTER_FUNC(fun_a, funa_implement)
REGISTER_FUNC(fun_b, funb_implement)
REGISTER_FUNC_END(CDemoB)

REGISTER_CLASS_C(CDemoB)

