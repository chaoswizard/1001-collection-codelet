#include "types.h"
#include "class_demoA.h"
#include "class_demoB.h"


int main()
{
	CDemoA  *clsA_ptr = NULL;
	CDemoB  *clsB_ptr = NULL;

	//单个类
	clsA_ptr = NEW_CLASS(CDemoA);

	if (clsA_ptr) {
		CLASS_FUNC_0P(CDemoA, clsA_ptr, fun_a);
		CLASS_FUNC_2P(CDemoA, clsA_ptr, fun_b, "singTst", 2);

		DEL_CLASS(CDemoA, clsA_ptr);
	}

	// 带有子类
	clsB_ptr = NEW_CLASS(CDemoB);

	if (clsB_ptr) {
		CLASS_FUNC_0P(CDemoB, clsB_ptr, fun_a);
		CLASS_FUNC_2P(CDemoB, clsB_ptr, fun_b, "MutiTst", 3);

		DEL_CLASS(CDemoB, clsB_ptr);
	}


	// 静态类
	{
		CLASS_DEFINE(CDemoB, clsB_instance);
		
		CLASS_FUNC_0P(CDemoB, &clsB_instance, fun_a);
		CLASS_FUNC_2P(CDemoB, &clsB_instance, fun_b, "StaticTst", 4);
		
		CLASS_UNDEFINE(CDemoB, clsB_instance);
	}
	return 0;
}

