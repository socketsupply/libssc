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

scripts=()
files=()
src=()

# shellcheck disable=SC2207
src+=($("$(which ls)" "$root"/include/**/*.h))
# shellcheck disable=SC2207
src+=($("$(which ls)" "$root"/src/*.c))

# shellcheck disable=SC2207
scripts+=($("$(which ls)" "$root"/scripts/*.sh))
# shellcheck disable=SC2207
scripts+=($("$(which ls)" "$root"/scripts/*.ps1))

for src in "${src[@]}"; do
  files+=("\"${src/$root\//}\"")
done

files_for_json="$(echo "${files[@]}" | sed 's/ /, /g' | sort)"

jq ".files |= [$files_for_json]" bpkg.json > bpkg.json.tmp
mv bpkg.json.tmp "$root/bpkg.json"

jq ".src |= [$files_for_json]" clib.json > clib.json.tmp
mv clib.json.tmp "$root/clib.json"

files=()
for script in "${scripts[@]}"; do
  files+=("\"${script/$root\//}\"")
done

scripts_for_json="$(echo "${files[@]}" | sed 's/ /, /g' | sort)"

jq ".scripts |= [$scripts_for_json]" bpkg.json > bpkg.json.tmp
mv bpkg.json.tmp "$root/bpkg.json"
