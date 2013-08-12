
#ifndef _SIMULATE_CLASS_H
#define _SIMULATE_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#define CLASS					typedef struct
#define CLASS_END(type)			type

//Declare a simple simulate constructor function for class
#define DECLARE_CONSTRUCTOR(type) \
	struct type * (* type##_constructor)(void* pthis)

//Declare a simple simulate destructor function for class
#define DECLARE_DESTRUCTOR(type) \
	void (* type##_destructor)(void * pthis)

#define CLASS_FUNC_NAME(name,pcnt) name##_func##pcnt##p

#define DECLARE_FUNC_0P(ret_type, name) \
	ret_type (* name##_func)(void * pthis)

#define DECLARE_FUNC_1P(ret_type, name, p1) \
	ret_type (* name##_func)(void * pthis, p1)


#define DECLARE_FUNC_2P(ret_type, name, p1, p2) \
	ret_type (* name##_func)(void * pthis, p1, p2)


#define DECLARE_FUNC_3P(ret_type, name, p1, p2, p3) \
	ret_type (* name##_func)(void * pthis, p1, p2, p3)


//the simulate construct fuction achieve, add the achieve code
//between DEFINE_CONSTRUCTOR_BEGIN and DEFINE_CONSTRUCTOR_END
#define DEFINE_CONSTRUCTOR_BEGIN(type) \
	static type * type##_constructor(void * pthis)
#define DEFINE_CONSTRUCTOR_END

//the simulate destructor fuction achieve, add the achieve code
//between DEFINE_DESTRUCTOR_BEGIN and DEFINE_DESTRUCTOR_END
#define DEFINE_DESTRUCTOR_BEGIN(type) \
	static void type##_destructor(void * pthis)
#define DEFINE_DESTRUCTOR_END

//construct fuction
#define CONSTRUCTOR_FUNC(type)	type##_constructor

//destruct fuction
#define DESTRUCTOR_FUNC(type)	type##_destructor

#if 0// gcc
//Register the function to the simulate class
#define REGISTER_FUNC_BEGIN(type, constructor_fun, destructor_fun) \
	type __this_Module_##type = { \
		.type##_constructor = constructor_fun, \
		.type##_destructor = destructor_fun,
#define REGISTER_FUNC(module_fun, fun) \
		.module_fun = fun,
#else
#define REGISTER_FUNC_BEGIN(type, constructor_fun, destructor_fun) \
	type __this_Module_##type = { \
		constructor_fun, \
		destructor_fun,
#define REGISTER_FUNC(module_fun, fun) \
		fun,
#endif
#define REGISTER_FUNC_END(type) \
	};

//Register the simulate class, declare the simulate new function
//and simulate delete function, this macro use in h file
#define REGISTER_CLASS_H(type) \
	type * simulate_new_##type();\
	void simulate_delete_##type(type *pdelete); \
	void load_##type##_module(type * pClass); \
	void unload_##type##_module(type * pClass)

//Register the simulate class, define the simulate new function
//and simulate delete function, this macro use in c file
#define REGISTER_CLASS_C(type) \
	type * simulate_new_##type() { \
		type * pclass = (type *)malloc(sizeof(type)); \
		if (NULL == pclass) { \
			return NULL; \
		} \
		memcpy(pclass, &__this_Module_##type, sizeof(type)); \
		\
		return pclass->type##_constructor(pclass); \
	} \
	\
	void simulate_delete_##type(type *pdelete) { \
		if (NULL == pdelete) \
			return; \
		\
		pdelete->type##_destructor(pdelete); \
		free(pdelete); \
	} \
	\
	void load_##type##_module(type * pClass) { \
		if (NULL == pClass) \
			return; \
		memcpy(pClass, &__this_Module_##type, sizeof(type)); \
		pClass->type##_constructor(pClass); \
	} \
	\
	void unload_##type##_module(type * pClass) { \
		if (NULL == pClass) \
			return; \
		pClass->type##_destructor(pClass);\
	}
	
//simulate new
#define NEW_CLASS(type) \
	simulate_new_##type()

//simulate delete
#define DEL_CLASS(type, DelPoint) \
	simulate_delete_##type(DelPoint)

//define simulate class code
#define CLASS_DEFINE(type, name) \
	type name; \
	load_##type##_module(&name)

//pairing of CLASS_DEFINE
#define CLASS_UNDEFINE(type, v) \
	unload_##type##_module(&v)


#define CLASS_FUNC_0P(type, cls_ptr, name) \
	(type *)(cls_ptr)->name##_func(cls_ptr)

#define CLASS_FUNC_1P(type, cls_ptr, name, p1) \
	(type *)(cls_ptr)->name##_func(cls_ptr, p1)

#define CLASS_FUNC_2P(type, cls_ptr, name, p1, p2) \
	(type *)(cls_ptr)->name##_func(cls_ptr, p1, p2)

#define CLASS_FUNC_3P(type, cls_ptr, name, p1, p2, p3) \
	(type *)(cls_ptr)->name##_func(cls_ptr, p1, p2, p3)


#ifdef __cplusplus
}
#endif

#endif
