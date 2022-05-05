#!/usr/bin/env bash
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

dirname="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
root="$(realpath "$dirname"/..)"

# shellcheck source=../deps/mush/mush.sh
source "$root/deps/mush/mush.sh"

name="$1"

## output usage
if [ -z "$name" ]; then
  echo 1>&2 "usage: $0 NAME"
  exit 1
fi

template="$root/templates/header.h"
output="$root/include/opc/$name.h"

if test -f "$output"; then
  rm -i "$output" || exit 1
fi

# shellcheck disable=SC2155
export HEADER="$(echo "$name" | tr '[:lower:]' '[:upper:]')"

cat < "$template" | mush > "$output"

exit $?
