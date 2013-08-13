
CXX             := $(PREFIX)g++
CC		:= $(PREFIX)gcc
AS		:= $(CC)

LD              := $(CXX)
#LD              := $(CC)


ifdef O
BUILD_DIR=$(O)
else
BUILD_DIR=BUILD_$(LOCAL_MODULE)_EXEC
endif

CXXFLAGS        := $(LOCAL_CFLAGS) $(addprefix -I,$(LOCAL_C_INCLUDES)) -Wall -D_GNU_SOURCE  -fms-extensions
CFLAGS		:= $(LOCAL_CFLAGS) $(addprefix -I,$(LOCAL_C_INCLUDES)) -Wall -D_GNU_SOURCE  -std=c99 -fms-extensions
LDFLAGS		:= $(LOCAL_LDFLAGS) $(addprefix -l,$(patsubst lib%,%,$(LOCAL_SHARED_LIBRARIES)))

OBJSC		:= $(patsubst %.c,$(BUILD_DIR)/%.o,$(LOCAL_SRC_CFILES))
OBJSCXX 	:= $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(LOCAL_SRC_CXXFILES))

OBJS 		:= $(OBJSCXX) $(OBJSC)
OBJ_DIRS	:= $(sort $(dir $(OBJS)))


.PHONY: all checkdirs clean rebuild

TARGET		:= $(BUILD_DIR)/$(LOCAL_MODULE)

all: checkdirs $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJSC): $(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJSCXX): $(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

checkdirs: $(OBJ_DIRS)

$(OBJ_DIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIRS)

rebuild: clean all
