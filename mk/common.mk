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

## Environment
OS = $(shell uname)
CWD := $(shell pwd)

## MAKE Configuration
MAKEFLAGS += --no-print-directory
THIS_MAKEFILE := $(dir $(firstword $(MAKEFILE_LIST)))

## Commands
CP = cp -rf
LN = ln -sf
RM = rm -rf
STRIP = strip
MKDIR = mkdir -p
_MKDIR = mkdir -p
ifneq ($(GCC),)
CC = gcc
else
ifneq ($(shell which clang 2>/dev/null),)
CC = clang
endif
endif

ifndef NO_VALGRIND
ifneq ($(shell which valgrind 2>/dev/null),)
VALGRIND ?= valgrind -q
endif
endif

## Project settings
LIBRARY_NAME ?= opc
LIBRARY_VERSION_MAJOR = 0
LIBRARY_VERSION_MINOR = 0
LIBRARY_VERSION_PATCH = 0
LIBRARY_VERSION_REVISION = $(shell $(THIS_MAKEFILE)/scripts/version.sh)
LIBRARY_DATE_COMPILED := $(shell date)
