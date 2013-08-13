include local_cfg
LOCAL_SRC_CFILES := \
		gnu_getopt.c \
		gnu_getopt_long.c


LOCAL_SRC_CXXFILES	:= \
		ccc.cpp

		
LOCAL_MODULE := test_make_c_cpp

LOCAL_CFLAGS := -rdynamic -ldl -ggdb

PREFIX := arm-none-linux-gnueabi-

LOCAL_SHARED_LIBRARIES := ggg bbbb
LOCAL_C_INCLUDES := ./include ./
LOCAL_LDFLAGS := -L$(MLibDir)  
include submodule/Make_config
include exec_rules.mk
