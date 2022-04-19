RM ?= $(shell which rm)
CWD ?= $(shell pwd)
BUILD_LIBRARY_PATH = $(shell realpath $(CWD)/../build/lib 2>/dev/null)

## Commands
CC ?= clang
LN ?= ln -sf
RM = rm -rf

ifndef NO_VALGRIND
VALGRIND ?= valgrind
endif

## test source files
SRC += $(wildcard *.c)
SRC += $(wildcard **/*.c)

## test target names which is just the
## source file without the .c extension
TARGETS = $(SRC:.c=)

## test compiler flags
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -I ../build/include
CFLAGS += -I ../deps
CFLAGS += -L $(BUILD_LIBRARY_PATH)
CFLAGS += -l opc
CFLAGS += -g

ifeq (Darwin, $(shell uname))
  CFLAGS += -framework Foundation
endif

## test dependency source files
DEPS += $(wildcard ../deps/ok/*.c)

## we need to set the LD_LIBRARY_PATH environment variable
## so our test executables can load the built library at runtime
export LD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)

## Configure brief.mk
-include ../mk/brief.mk

default: $(TARGETS)
	@for t in $^; do                                \
	  printf '\n## %s\n' $$t;                       \
		$(VALGRIND) ./$$t; \
	  printf '...\n' $$t;                           \
  done

$(TARGETS): $(SRC)
	$(CC) -o $@ $@.c $(DEPS) $(CFLAGS) -D OK_EXPECTED=`cat $(@).c|grep 'ok('|wc -l`

.PHONY: clean
clean: BRIEF_ARGS = $(TARGETS)
clean:
	@for target in $(TARGETS); do printf " " && printf $(BRIEF_FORMAT) "RM" " test/$$target"; done
