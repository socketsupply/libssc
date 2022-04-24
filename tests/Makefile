CWD ?= $(shell pwd)
BUILD_LIBRARY_PATH = ../build/lib

MAKEFLAGS += --no-print-directory

## Commands
CC ?= clang
LN ?= ln -sf
RM = rm -rf

ifndef NO_VALGRIND
ifneq ($(shell which valgrind 2>/dev/null),)
VALGRIND ?= valgrind -q
endif
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
DEPS +=

## we need to set the LD_LIBRARY_PATH environment variable
## so our test executables can load the built library at runtime
export LD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)

## Configure brief.mk
#BRIEF_FORMAT ?= "  %s\t%s\n"
-include ../mk/brief.mk

default: $(TARGETS)

$(TARGETS): $(SRC)
	@echo
	$(CC) -o $@ $@.c $(DEPS) $(CFLAGS) -D OK_EXPECTED=`cat $(@).c|grep 'ok('|wc -l`
	@echo
ifdef VALIDATE_WITH_TAP_PARSER
	@$(VALGRIND) ./$@ | ../node_modules/.bin/tap-parser --tap
else
	@$(VALGRIND) ./$@
endif

.PHONY: clean
clean:
ifndef NO_BRIEF
	@rm -rf $(TARGETS)
	@for target in $(TARGETS); do printf " " && printf $(BRIEF_FORMAT) "RM" " test/$$target"; done
else
	rm -rf $(TARGETS)
endif
