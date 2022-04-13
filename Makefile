##
# `libopc`
# MIT License
# Copyright (c) 2022 Socket Supply Co.
##

-include deps/brief.mk/brief.mk

OS = $(shell uname)
CWD = $(shell pwd)

SRC = $(wildcard $(CWD)/src/**/*.c)
OBJS := $(SRC:.c=.o)

CFLAGS += -Iinclude
export SRC
export CFLAGS
export LDFLAGS

default: build
	@:

build: $(SRC)

tests: test

test:
	@:
