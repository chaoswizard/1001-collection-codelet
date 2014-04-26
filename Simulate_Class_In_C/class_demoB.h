#include "simcls_define.h"


#ifdef __cplusplus
extern "C" {
#endif


CLASS 
{	
	//declare the constructor function is point
	DECLARE_CONSTRUCTOR(CDemoB);
	//declare the destructor fucntion is point
	DECLARE_DESTRUCTOR(CDemoB);

	//member function and method
	DECLARE_FUNC_0P(int, fun_a);
	DECLARE_FUNC_2P(int, fun_b, char *, int);

	//member variable storage struct point, user should never change it
	void *interface;
} CLASS_END(CDemoB);

REGISTER_CLASS_H(CDemoB);




#ifdef __cplusplus
}
#endif


