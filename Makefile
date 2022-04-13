##
# `libopc`
# MIT License
# Copyright (c) 2022 Socket Supply Co.
##

## Configure brief.mk
BRIEFC += CC RM
-include deps/brief.mk/brief.mk

## Environment
OS = $(shell uname)
CWD = $(shell pwd)

## Targets
SRC = $(wildcard src/**/*.c)
OBJS := $(SRC:.c=.o)

## Compiler
CFLAGS += -Iinclude
LDFLAGS +=

export SRC
export CFLAGS
export LDFLAGS

default: build
	@:

build: $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

tests: test

test:
	@:

clean: CLEAN_TARGETS = $(OBJS)
clean: BRIEF_ARGS = $(CLEAN_TARGETS)
clean:
	$(RM) $(CLEAN_TARGETS)
