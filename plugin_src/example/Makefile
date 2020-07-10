default: all

NAME := example

PLUGIN_DIR ?= ../../plugins

CFLAGS := -shared -fPIC -DNON_MATCHING -DAVOID_UB
LDFLAGS := -Wl,-rpath=.
INCLUDES := -I../../ -I../../include -I../../src

ifeq ($(TARGET_WINDOWS),1)
	LIB_EXT ?= dll
else
	LIB_EXT ?= so
endif

all: example.c
	$(CROSS)gcc ${CFLAGS} ${LDFLAGS} ${INCLUDES} $^ -o ${PLUGIN_DIR}/${NAME}.${LIB_EXT}

.PHONY: default all test