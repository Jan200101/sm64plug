default: all

NAME := example

PLUGIN_DIR ?= ../../plugins

CFLAGS := -shared -fPIC
LDFLAGS := -Wl,-rpath=.
INCLUDES := -I../../src/

ifeq ($(TARGET_WINDOWS),1)
	LIB_EXT ?= dll
	CFLAGS += -L.. -l$(TARGET)
else
	LIB_EXT ?= so
endif

all: example.c
	$(CROSS)gcc $(CFLAGS) $(LDFLAGS) $^ -o $(PLUGIN_DIR)/$(NAME).$(LIB_EXT) $(INCLUDES)

.PHONY: default all test