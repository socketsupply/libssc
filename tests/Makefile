##
# `libopc` - Operator Framework Client Library
#
# This file is part of libopc.
#
# MIT License
#
# Copyright (c) 2022 Socket Supply Co.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
##

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

## Makefile includes
-include ../mk/common.mk
-include ../mk/brief.mk

default: $(TARGETS)

$(TARGETS): $(SRC)
	@echo
	$(CC) -o $@ $@.c $(DEPS) $(CFLAGS) -D OK_EXPECTED=`cat $(@).c|grep 'ok('|wc -l`
	@echo
ifdef VALIDATE_WITH_TAP_PARSER
	@{ $(VALGRIND) ./$@ | ../node_modules/.bin/tap-parser --tap; } || { rm -rf $@ && false; }
else
	@{ $(VALGRIND) ./$@; } || { rm -rf $@ && false; }
endif

.PHONY: clean
clean:
ifndef NO_BRIEF
	@rm -rf $(TARGETS)
	@for target in "$(TARGETS)"; do if test -f "$$target"; then printf " " && printf $(BRIEF_FORMAT) "RM" " test/$$target"; fi; done
else
	$(RM) -rf $(TARGETS)
endif
