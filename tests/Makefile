##
# `libssc` - Socket SDK Client Library
#
# This file is part of libssc.
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

## Makefile includes
include ../mk/common.mk
-include ../mk/brief.mk

BUILD_LIBRARY_PATH = $(realpath $(MAKEFILE_DIRNAME)/../build/lib)

## test source files
SRC += $(wildcard *.c)
SRC += $(wildcard **/*.c)

LIBRARY_SOURCES += $(wildcard ../build/include/**/*.h)
LIBRARY_SOURCES += $(wildcard ../include/**/*.h)
LIBRARY_SOURCES += $(wildcard ../src/*.c)

## test target names which is just the
## source file without the .c extension
TARGETS = $(SRC:.c=)

## test compiler flags
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -I ../build/include -I ../deps
CFLAGS += -L $(BUILD_LIBRARY_PATH)
CFLAGS += -l ssc

ifeq (Darwin, $(shell uname))
  CFLAGS += -framework Foundation
endif

## test dependency source files
DEPS +=

## we need to set the LD_LIBRARY_PATH environment variable
## so our test executables can load the built library at runtime
export LD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_FALLBACK_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)

default: $(TARGETS)


$(TARGETS): $(SRC) $(LIBRARY_SOURCES) Makefile
ifdef FAST
	@$(foreach target, $(TARGETS), $(_CC) -o $(target) $(target).c $(DEPS) $(CFLAGS);)
ifdef VALIDATE_TAP
	@$(foreach target, $(TARGETS), $(VALGRIND) $(target) | ../node_modules/.bin/tap-parser --tap;)
else
	@$(foreach target, $(TARGETS), $(VALGRIND) $(target);)
endif
else
	@echo
	$(CC) -o $@ $@.c $(DEPS) $(CFLAGS)
	@echo
ifdef VALIDATE_TAP
	@{ $(VALGRIND) ./$@ | ../node_modules/.bin/tap-parser --tap; } || { rm -rf $@ && exit 1; }
else
	@{ $(VALGRIND) ./$@; } || { rm -rf $@ && exit 1; }
endif
endif

.PHONY: clean
clean:
ifndef NO_BRIEF
	@rm -rf $(TARGETS)
	@for target in "$(TARGETS)"; do if test -f "$$target"; then printf " " && printf $(BRIEF_FORMAT) "RM" " test/$$target"; fi; done
else
	$(RM) -rf $(TARGETS)
endif
