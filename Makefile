##
# `libopc`
# MIT License
# Copyright (c) 2022 Socket Supply Co.
##

## Environment
OS = $(shell uname)
CWD = $(shell pwd)

## Commands
CC ?= clang
CP = cp -rf
LN ?= ln -sf
RM = rm -rf
STRIP = strip
MKDIR = mkdir -p
_MKDIR = mkdir -p

MAKEFLAGS += --no-print-directory

## Configure brief.mk
-include ./mk/brief.mk

## Project settings
LIBRARY_NAME ?= opc
LIBRARY_VERSION_MAJOR = 0
LIBRARY_VERSION_MINOR = 0
LIBRARY_VERSION_PATCH = 0
LIBRARY_VERSION_REVISION = $(shell scripts/version.sh)
LIBRARY_DATE_COMPILED := $(shell date)

## Targets
SRC += $(wildcard src/**/*.c)
SRC += $(wildcard src/*.c)
OBJS := $(SRC:.c=.o)
HEADERS += $(wildcard include/**/*.h)

## Target static library
STATIC := lib$(LIBRARY_NAME).a
SOLIB := lib$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
DYLIB := lib$(LIBRARY_NAME).$(LIBRARY_VERSION_MAJOR).$(LIBRARY_VERSION_MINOR).dylib
SO := lib$(LIBRARY_NAME).so

## Build configuration
BUILD_DIRECTORY ?= build
BUILD_INCLUDE ?= $(BUILD_DIRECTORY)/include
BUILD_LIB ?= $(BUILD_DIRECTORY)/lib

## Compiler
CFLAGS += -Iinclude -Ideps
ifeq ($(OS), Darwin)
	LDFLAGS += -shared -lc -Wl,-install_name,$(SO)
else
	LDFLAGS += -shared -Wl,-soname,$(SO).$(LIBRARY_VERSION_MAJOR)
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

## Macro to ensure build directory structure is in place
define ENSURE_BUILD_DIRECTORY_STRUCTURE
@mkdir -p $(BUILD_DIRECTORY)/include/$(LIBRARY_NAME) &&   \
 mkdir -p $(BUILD_DIRECTORY)/lib;
endef

default: build
	@:

install: build
	@echo "Not implemented"

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
	$(CC) $(LDFLAGS) -dynamiclib -undefined suppress -flat_namespace $^ -o $@
endif

## Compiles and runs all test
.PHONY: tests
tests: test
.PHONY: test
test: build
	@$(MAKE) -C tests

## Cleans test directory
.PHONY: tests/clean
tests/clean: BRIEF_ARGS = clean (test)
tests/clean:
	@$(MAKE) -C tests clean

.PHONY: examples/clean
examples/clean: BRIEF_ARGS = clean (examples)
examples/clean:
	@:

clean: tests/clean
clean: examples/clean
clean:
ifndef NO_BRIEF
	@rm -rf $(CLEAN_TARGETS)
	@for target in $(CLEAN_TARGETS); do printf " " && printf $(BRIEF_FORMAT) "RM" " $$target"; done
else
	rm -rf $(CLEAN_TARGETS)
endif
