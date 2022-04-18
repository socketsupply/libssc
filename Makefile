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

## Configure brief.mk
BRIEFC += AR CC CP LN MKDIR RM STRIP
#-include deps/brief.mk/brief.mk

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

## Tests
TESTS_DEPS += $(wildcard deps/ok/*.c)
TESTS_SRC += $(wildcard tests/**/*.c)
TESTS_SRC += $(wildcard tests/*.c)
TESTS = $(TESTS_SRC:.c=)

## Compiler
CFLAGS += -Iinclude -Ideps
ifeq ($(OS), Darwin)
	LDFLAGS += -shared -lc -Wl,-install_name,$(TARGET_SO)
else
	LDFLAGS += -shared -Wl,-soname,$(TARGET_SO).$(LIBRARY_VERSION_MAJOR)
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

## Exports
export SRC
export CFLAGS
export LDFLAGS

## Macro to ensure build directory structure is in place
define ENSURE_BUILD_DIRECTORY_STRUCTURE
@if ! test -d $(BUILD_DIRECTORY); then                          \
	printf " ";                                                   \
	printf $(BRIEF_FORMAT) "MKDIR"                                \
	" $(BUILD_DIRECTORY)/{include/$(LIBRARY_NAME),lib}"           \
	| tr '\n' ' ' && echo;                                        \
	$(_MKDIR) $(BUILD_DIRECTORY)/include/$(LIBRARY_NAME);         \
	$(_MKDIR) $(BUILD_DIRECTORY)/lib;                             \
fi
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
build: $(BUILD_LIB)/$(STATIC)
build: $(BUILD_LIB)/$(SO)
build: $(BUILD_LIB)/$(SOLIB)
ifeq ($(OS),Darwin)
build: $(BUILD_LIB)/$(DYLIB)
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
$(BUILD_INCLUDE)/$(LIBRARY_NAME): $(HEADERS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(MKDIR) $@
	$(CP) $(HEADERS) $@

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
$(BUILD_LIB)/$(SOLIB): $(BUILD_LIB)/$(SO)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(LN) $(shell basename $<) $@
	$(LN) $(shell basename $<) $@.$(LIBRARY_VERSION_MINOR)
	$(LN) $(shell basename $<) $@.$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH)
	$(LN) $(shell basename $<) $@.$(LIBRARY_VERSION_MINOR).$(LIBRARY_VERSION_PATCH).$(LIBRARY_VERSION_REVISION)

## Builds dynamic libary
ifeq ($(OS),Darwin)
.PHONY: $(DYLIB)
$(DYLIB): $(BUILD_LIB)/$(DYLIB)
$(BUILD_LIB)/$(DYLIB): $(OBJS)
	$(ENSURE_BUILD_DIRECTORY_STRUCTURE)
	$(CC) $(LDFLAGS) -dynamiclib -undefined suppress -flat_namespace $^ -o $@
endif

## Cleans test directory
.PHONY: test/clean
test/clean: BRIEF_ARGS = clean (test)
test/clean:
	if test -d test; then $(MAKE) clean -C test; fi
## Compiles and runs all test
.PHONY: test
test: build
	$(MAKE) -C tests

.PHONY: $(TESTS_SRC)
$(TESTS_SRC):
	$(CC) $(CFLAGS) $@ -o $(@:.c=)

clean: BRIEF_ARGS = $(CLEAN_TARGETS)
clean:
	$(RM) $(CLEAN_TARGETS)
