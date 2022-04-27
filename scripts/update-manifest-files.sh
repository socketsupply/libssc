#!/usr/bin/env bash

dirname="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
root="$(realpath "$dirname"/..)"
files=()
src=()

# shellcheck disable=SC2207
src+=($("$(which ls)" "$root"/include/**/*.h))
# shellcheck disable=SC2207
src+=($("$(which ls)" "$root"/src/*.c))

for src in "${src[@]}"; do
  files+=("\"${src/$root\//}\"")
done

files_for_json="$(echo "${files[@]}" | sed 's/ /, /g' | sort)"

jq ".files |= [$files_for_json]" bpkg.json > bpkg.json.tmp
jq ".src |= [$files_for_json]" clib.json > clib.json.tmp

mv bpkg.json.tmp "$root/bpkg.json"
mv clib.json.tmp "$root/clib.json"
