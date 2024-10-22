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

CC ?= clang
RM = rm -rf
MKDIR = mkdir -p

CWD ?= $(shell pwd)
TARGET = hello-world
SRC = $(wildcard src/*.c)

ifdef PREFIX
PREFIX := $(CWD)/$(PREFIX)
else
PREFIX := $(CWD)/build
endif

LIBSSC = ../../build/lib/libssc.a

CFLAGS += -I ../../build/include
CFLAGS += -Werror
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -g

include $(CURDIR)/../../mk/brief.mk

## we need to set the LD_LIBRARY_PATH environment variable
## so our test executables can load the built library at runtime
export LD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH = $(BUILD_LIBRARY_PATH)

default: build

build: $(PREFIX)/bin/$(TARGET) $(PREFIX)/lib/libssc.a
	cp -f src/*.html $(PREFIX)

$(PREFIX)/lib/libssc.a: $(LIBSSC)

$(LIBSSC):
	$(MAKE) -C ../.. install-library PREFIX=$(PREFIX)

$(PREFIX)/bin/$(TARGET): $(LIBSSC)
	$(MKDIR) `dirname $@`
	$(CC) $(SRC) $(LIBSSC)  $(CFLAGS) -o $@

clean:
	@rm -rf build/
