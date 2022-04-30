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

## Configure brief.mk (before including)
BRIEFC += MAN

## Makfile includes
include ./mk/common.mk
-include ./mk/brief.mk

MAN = marked-man
NPM ?= npm

MARKEDMAN_BIN = ./node_modules/.bin/marked-man

## Dependencies
DEPS += $(wildcard deps/flag/*.c)

## Targets
SRC += $(wildcard src/**/*.c)
SRC += $(wildcard src/*.c)
SRC += $(DEPS)
OBJS := $(SRC:.c=.o)
HEADERS += $(wildcard include/**/*.h)

## Target static library
STATIC := lib$(LIBRARY_NAME).a
SOLIB := lib$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
DYLIB := lib$(LIBRARY_NAME).dylib
SO := lib$(LIBRARY_NAME).so

## man 3 files
MAN_SOURCES = $(wildcard man/*.md)
MAN_TARGETS = $(MAN_SOURCES:.md=)

## Build configuration
BUILD_DIRECTORY ?= build
BUILD_INCLUDE ?= $(BUILD_DIRECTORY)/include
BUILD_LIB ?= $(BUILD_DIRECTORY)/lib

## Compiler
CFLAGS += -std=c99
CFLAGS += -Iinclude -Ideps
ifeq ($(OS), Darwin)
	LDFLAGS += -shared -lc -Wl,-install_name,$(DYLIB)
	LDFLAGS += -dynamiclib -undefined suppress -flat_namespace
else
	LDFLAGS += -shared -Wl,-soname,$(SO).$(LIBRARY_VERSION_MAJOR)
	CFLAGS += -fPIC
endif

## Misc
CLEAN_TARGETS = $(OBJS)
CLEAN_TARGETS += $(BUILD_INCLUDE)/$(LIBRARY_NAME)
CLEAN_TARGETS += $(BUILD_LIB)/$(STATIC)
CLEAN_TARGETS += $(BUILD_LIB)/$(SOLIB)
CLEAN_TARGETS += $(wildcard $(BUILD_LIB)/$(SOLIB).*)
CLEAN_TARGETS += $(BUILD_LIB)/$(SO)
ifeq ($(OS),Darwin)
CLEAN_TARGETS += $(BUILD_LIB)/$(DYLIB)
endif

## Tests
TEST_SOURCES = $(wildcard tests/*.c)
TEST_TARGETS = $(TEST_SOURCES:.c=)

## Macro to ensure build directory structure is in place
define ENSURE_BUILD_DIRECTORY_STRUCTURE
@mkdir -p $(BUILD_DIRECTORY)/include/$(LIBRARY_NAME) &&   \
 mkdir -p $(BUILD_DIRECTORY)/lib;
endef

export PATH := $(CWD)/node_modules/.bin:$(PATH)

default: build
	@:

install: build

uninstall:
	@echo "Not implemented"

## Builds
build: $(OBJS)
build: $(BUILD_INCLUDE)/$(LIBRARY_NAME)
build: $(STATIC)
build: $(SO)
build: $(SOLIB)
ifeq ($(OS),Darwin)
build: $(DYLIB)
endif
build: man

node_modules:
	$(NPM) install >/dev/null

$(MARKEDMAN_BIN): node_modules
	@:

## Builds objects
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

## Builds static library
.PHONY: $(STATIC)
$(STATIC): $(BUILD_LIB)/$(STATIC)
$(BUILD_LIB)/$(STATIC): $(OBJS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(AR) crs $@ $^

## Copies header files
.PHONY: $(BUILD_INCLUDE)/$(LIBRARY_NAME)
$(BUILD_INCLUDE)/$(LIBRARY_NAME): BRIEF_ARGS = $(HEADERS) -> $@
$(BUILD_INCLUDE)/$(LIBRARY_NAME): $(HEADERS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
ifndef NO_BRIEF
	@cp -rf $(HEADERS) $@
	@for header in $(HEADERS); do printf " " && printf $(BRIEF_FORMAT) "CP" "$$(printf " %s\t~>\t%s" "$$header" "$@")"; done
else
	cp -rf $(HEADERS) $@
endif

## Builds a shared object
.PHONY: $(SO)
$(SO): $(BUILD_LIB)/$(SO)
$(BUILD_LIB)/$(SO): $(OBJS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS)
ifneq ($(OS),Darwin)
	$(STRIP) --strip-unneeded $@
endif

## Links shared object to name with major version
.PHONY: $(SOLIB)
$(SOLIB): $(BUILD_LIB)/$(SOLIB)
$(SOLIB): $(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR)
$(SOLIB): $(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH)
$(SOLIB): $(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH).$(LIBRARY_VERSION_REVISION)
$(BUILD_LIB)/$(SOLIB): $(BUILD_LIB)/$(SO)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(LN) $(shell basename $<) $@

$(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR): $(BUILD_LIB)/$(SO)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(LN) $(shell basename $<) $@

$(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH): $(BUILD_LIB)/$(SO)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(LN) $(shell basename $<) $@

$(BUILD_LIB)/$(SOLIB).$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH).$(LIBRARY_VERSION_REVISION): $(BUILD_LIB)/$(SO)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(LN) $(shell basename $<) $@

## Builds dynamic libary
ifeq ($(OS),Darwin)
.PHONY: $(DYLIB)
$(DYLIB): $(BUILD_LIB)/$(DYLIB)
$(BUILD_LIB)/$(DYLIB): $(OBJS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(CC) $(LDFLAGS) $^ -o $@
endif

.PHONY: man
man: $(MAN_TARGETS)

.PHONY: man/clean
man/clean: BRIEF_ARGS = clean (man)
man/clean:
	$(RM) $(MAN_TARGETS)

$(MAN_TARGETS): $(MARKEDMAN_BIN)
$(MAN_TARGETS): $(MAN_SOURCES)
	@rm -f $@
	$(MAN) $@.md > $@

## Compiles and runs all test
.PHONY: tests
test: tests
tests: $(TEST_TARGETS)

$(TEST_TARGETS): build $(TEST_SOURCES)
	@$(MAKE) -B -C tests `basename $@`

## Cleans test directory
.PHONY: tests/clean
tests/clean: BRIEF_ARGS = clean (test)
tests/clean:
	@$(MAKE) -C tests clean

.PHONY: examples/clean
examples/clean: BRIEF_ARGS = clean (examples)
examples/clean:
	$(MAKE) -C examples/hello-world clean

clean: man/clean
clean: tests/clean
clean: examples/clean
clean:
ifndef NO_BRIEF
	@rm -rf $(CLEAN_TARGETS)
	@for target in $(CLEAN_TARGETS); do printf " " && printf $(BRIEF_FORMAT) "RM" " $$target"; done
else
	rm -rf $(CLEAN_TARGETS)
endif
