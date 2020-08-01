default: all

NAME := discordrpc

PLUGIN_DIR ?= ../../plugins

CFLAGS := -shared -fPIC -DNON_MATCHING -DAVOID_UB
LDFLAGS := -Wl,-rpath=.
INCLUDES := -I../../ -I../../src/ -I../../include 

ifeq ($(TARGET_WINDOWS),1)
	LIB_EXT ?= dll
	CFLAGS += -L.. -l$(TARGET)
else
	LIB_EXT ?= so
endif

all: discordrpc.c
	$(CROSS)gcc $(CFLAGS) $(LDFLAGS) $^ -o $(PLUGIN_DIR)/$(NAME).$(LIB_EXT) $(INCLUDES)

.PHONY: default all test