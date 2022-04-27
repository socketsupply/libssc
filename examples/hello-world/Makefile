CC ?= clang
RM = rm -rf
MKDIR = mkdir -p

CWD ?= $(shell pwd)
TARGET = hello-world
SRC = $(wildcard src/*.c)

ifdef PREFIX
PREFIX := $(CWD)/$(PREFIX)
else
PREFIX := $(CWD)/build
endif

LIBOPC = ../../build/lib/libopc.a

CFLAGS += -I ../../build/include
CFLAGS += -Werror
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -g

include $(CURDIR)/../../mk/brief.mk

## we need to set the LD_LIBRARY_PATH environment variable
## so our test executables can load the built library at runtime
export LD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)

default: build

build: $(PREFIX)/bin/$(TARGET)

$(LIBOPC):
	$(MAKE) -C ../..

$(PREFIX)/bin/$(TARGET): $(LIBOPC)
	$(MKDIR) `dirname $@`
	$(CC) $(SRC) $(LIBOPC)  $(CFLAGS) -o $@

clean:
	rm -rf $(PREFIX)/$(TARGET)
