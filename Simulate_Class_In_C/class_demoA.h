#include "simcls_define.h"


#ifdef __cplusplus
extern "C" {
#endif


CLASS {	
	//declare the constructor function is point
	DECLARE_CONSTRUCTOR(CDemoA);
	//declare the destructor fucntion is point
	DECLARE_DESTRUCTOR(CDemoA);
	
	DECLARE_FUNC_0P(int, fun_a);
	DECLARE_FUNC_2P(int, fun_b, char *, int);
	//member variable storage struct point, user should never change it
	void *interface;
} CLASS_END(CDemoA);

REGISTER_CLASS_H(CDemoA);




#ifdef __cplusplus
}
#endif


