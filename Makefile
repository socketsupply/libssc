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
MAN = marked-man
NPM ?= npm

BRIEFC += MAN

## Makfile includes
include ./mk/common.mk
-include ./mk/brief.mk

PREFIX ?= /usr/local

## Build configuration
BUILD_DIRECTORY ?= build
BUILD_INCLUDE ?= $(BUILD_DIRECTORY)/include
BUILD_LIB ?= $(BUILD_DIRECTORY)/lib

MARKEDMAN_BIN = ./node_modules/.bin/marked-man

## Dependencies
DEPS += $(wildcard deps/flag/*.c)

## Targets
SRC += $(wildcard src/**/*.c)
SRC += $(wildcard src/*.c)
SRC += $(DEPS)
OBJS := $(SRC:.c=.o)
HEADERS += $(wildcard include/**/*.h)

## Target headers
HEADER_TARGETS = $(foreach target,$(HEADERS),$(BUILD_DIRECTORY)/$(target))

## Target static library
STATIC := lib$(LIBRARY_NAME).a
SOLIB := lib$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
DYLIB := lib$(LIBRARY_NAME).dylib
SO := lib$(LIBRARY_NAME).so

## man 3 files
MAN3_SOURCES = $(wildcard man/man3/*.3.md)
MAN3_TARGETS = $(foreach target,$(MAN3_SOURCES:.md=),$(BUILD_DIRECTORY)/man/man3/$(shell basename $(target)))

LIBRARY_INSTALL_TARGETS += $(PREFIX)/lib/$(STATIC)
LIBRARY_INSTALL_TARGETS += $(PREFIX)/lib/$(SOLIB)
LIBRARY_INSTALL_TARGETS += $(PREFIX)/lib/$(SO)
ifeq ($(OS), Darwin)
LIBRARY_INSTALL_TARGETS += $(PREFIX)/lib/$(DYLIB)
endif

MAN3_INSTALL_TARGETS += $(foreach target,$(MAN3_TARGETS),$(PREFIX)/man/man3/$(shell basename $(target)))

HEADER_INSTALL_TARGETS += $(foreach target,$(HEADER_TARGETS),$(PREFIX)/include/$(LIBRARY_NAME)/$(shell basename $(target)))

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
CLEAN_TARGETS += $(BUILD_INCLUDE)/$(LIBRARY_NAME)
CLEAN_TARGETS += $(BUILD_LIB)/$(STATIC)
CLEAN_TARGETS += $(BUILD_LIB)/$(SOLIB)
CLEAN_TARGETS += $(wildcard $(BUILD_LIB)/$(SOLIB).*)
CLEAN_TARGETS += $(BUILD_LIB)/$(SO)
ifeq ($(OS),Darwin)
CLEAN_TARGETS += $(BUILD_LIB)/$(DYLIB)
endif

CLEAN_TARGETS += $(OBJS)

## Tests
TEST_SOURCES = $(wildcard tests/*.c)
TEST_TARGETS = $(TEST_SOURCES:.c=)

## Macro to ensure build directory structure is in place
define ENSURE_BUILD_DIRECTORY_STRUCTURE
@test -d $(BUILD_DIRECTORY)/include/$(LIBRARY_NAME) || mkdir -p $(BUILD_DIRECTORY)/include/$(LIBRARY_NAME);
@test -d $(BUILD_DIRECTORY)/lib || mkdir -p $(BUILD_DIRECTORY)/lib;
@test -d $(BUILD_DIRECTORY)/man/man1 || mkdir -p $(BUILD_DIRECTORY)/man/man1;
@test -d $(BUILD_DIRECTORY)/man/man3 || mkdir -p $(BUILD_DIRECTORY)/man/man3;
endef

define ENSURE_PREFIX_DIRECTORY_STRUCTURE
@test -d $(PREFIX)/include/$(LIBRARY_NAME) || mkdir -p $(PREFIX)/include/$(LIBRARY_NAME);
@test -d $(PREFIX)/lib || mkdir -p $(PREFIX)/lib;
@test -d $(PREFIX)/man/man1 || mkdir -p $(PREFIX)/man/man1;
@test -d $(PREFIX)/man/man3 || mkdir -p $(PREFIX)/man/man3;
endef

export PATH := $(CWD)/node_modules/.bin:$(PATH)

default: build
	@:

install: build install-headers install-library install-man
install-headers: $(HEADER_INSTALL_TARGETS)
install-library: $(LIBRARY_INSTALL_TARGETS)
install-man: install-man3
install-man3: $(MAN3_INSTALL_TARGETS)

uninstall: uninstall-headers uninstall-library uninstall-man
uninstall-headers: BRIEF_ARGS = $(PREFIX)/include/$(LIBRARY_NAME)
uninstall-headers:
	$(RM) $(PREFIX)/include/$(LIBRARY_NAME)

uninstall-library: BRIEF_ARGS = $(PREFIX)/lib/{$(foreach target,$(LIBRARY_INSTALL_TARGETS),$(shell basename $(target)))}
uninstall-library:
	$(RM) $(LIBRARY_INSTALL_TARGETS)

uninstall-man: uninstall-man3
uninstall-man3: BRIEF_ARGS = $(PREFIX)/man/man3/{$(foreach target,$(MAN3_INSTALL_TARGETS),$(shell basename $(target)))}
uninstall-man3:
	$(RM) $(MAN3_INSTALL_TARGETS)

$(HEADER_INSTALL_TARGETS): $(HEADER_TARGETS)
	$(ENSURE_PREFIX_DIRECTORY_STRUCTURE)
	$(CP) $(subst $(PREFIX),$(BUILD_DIRECTORY),$@) $@

$(LIBRARY_INSTALL_TARGETS): $(LIBRARY_TARGETS)
	$(ENSURE_PREFIX_DIRECTORY_STRUCTURE)
	$(INSTALL) -b $(subst $(PREFIX),$(BUILD_DIRECTORY),$@) $@

$(MAN3_INSTALL_TARGETS): $(MAN3_TARGETS)
	$(ENSURE_PREFIX_DIRECTORY_STRUCTURE)
	$(CP) $(subst $(PREFIX),$(BUILD_DIRECTORY),$@) $@

## All build dependencies
build: $(OBJS) $(HEADER_TARGETS)
build: build/lib
build: build/man

## Build libraries
build/lib: $(BUILD_INCLUDE)/$(LIBRARY_NAME)
build/lib: $(STATIC)
build/lib: $(SO)
build/lib: $(SOLIB)
ifeq ($(OS),Darwin)
build/lib: $(DYLIB)
endif

## Build man pages
build/man: $(MAN3_TARGETS)

## Install nodejs modules for tooling
node_modules:
	$(NPM) install >/dev/null

## Install `marked-man`
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
$(BUILD_INCLUDE)/$(LIBRARY_NAME): $(HEADER_TARGETS)

$(HEADER_TARGETS): $(HEADERS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(CP) $(subst $(BUILD_DIRECTORY),.,$@) $@

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
man: $(MAN3_TARGETS)

.PHONY: man/clean
man/clean: BRIEF_ARGS = build/man
man/clean:
	$(RM) $(MAN3_TARGETS)

$(MAN3_TARGETS): $(MARKEDMAN_BIN)
$(MAN3_TARGETS): BRIEF_ARGS = $(BUILD_DIRECTORY)/$@
$(MAN3_TARGETS): $(MAN3_SOURCES)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	@rm -f $@
	$(MAN) $(subst $(BUILD_DIRECTORY),.,$@).md > $@

## Compiles and runs all test
.PHONY: tests test
test: tests
tests: $(TEST_TARGETS) build

$(TEST_TARGETS): $(TEST_SOURCES) $(SRC) $(HEADERS) $(HEADER_TARGETS) tests/Makefile Makefile build
	@$(MAKE) -B -C tests `basename $@`

## Cleans test directory
.PHONY: tests/clean
tests/clean: BRIEF_ARGS = clean (test)
tests/clean:
	@$(MAKE) -C tests clean

.PHONY: examples/clean
examples/clean: BRIEF_ARGS = clean (examples)
examples/clean:
	@$(MAKE) -C examples/hello-world clean

.PHONY: clean
clean: man/clean
clean: targets/clean
clean: tests/clean
clean: examples/clean
clean: BRIEF_ARGS = $(BUILD_DIRECTORY) tmp
clean:
	$(RM) $(BUILD_DIRECTORY) ./tmp/

targets/clean:
ifndef NO_BRIEF
	@rm -rf $(CLEAN_TARGETS)
	@for target in $(CLEAN_TARGETS); do printf " " && printf $(BRIEF_FORMAT) "RM" " $$target"; done
else
	rm -rf $(CLEAN_TARGETS)
endif

compile_flags: compile_flags.txt
compile_flags.txt: BRIEF_ARGS = $@
compile_flags.txt: Makefile
	$(RM) -f $@
	@$(call BRIEF_ECHO, CREATE, $@)
	@echo $(CFLAGS) | sed 's/\s/\n/g' > $@

tidycheck: tidy check
tidylintcheck: tidy lint check

.PHONY: check
check: BRIEF_ARGS = src/*.c include/$(LIBRARY_NAME)/*.h test/*.c
check: compile_flags.txt
check: $(SRC) $(HEADERS) $(TEST_SOURCES)
ifneq ($(CHECK),)
	$(CHECK) $(filter-out $(DEPS), $(SRC)) $(HEADERS) $(TEST_SOURCES)
endif

.PHONY: tidy
tidy: BRIEF_ARGS = src/*.c include/$(LIBRARY_NAME)/*.h test/*.c
tidy: .clang-tidy $(SRC) $(HEADERS) $(TEST_SOURCES)
ifneq ($(TIDY),)
	$(TIDY) $(filter-out $(DEPS), $(SRC)) $(HEADERS) $(TEST_SOURCES)
endif

.PHONY: lint
lint: BRIEF_ARGS = src/*.c include/$(LIBRARY_NAME)/*.h test/*.c
lint: $(SRC) $(HEADERS) $(TEST_SOURCES)
ifneq ($(LINT),)
	$(LINT) $(filter-out $(DEPS), $(SRC)) $(HEADERS) $(TEST_SOURCES)
endif

.clang-tidy: BRIEF_ARGS = $@
.clang-tidy: $(SRC) $(HEADERS) $(TEST_SOURCES) Makefile
ifneq ($(TIDY),)
	$(RM) $@
	$(TIDY) --checks="-*,clang-analyzer-*" --dump-config > $@
endif
