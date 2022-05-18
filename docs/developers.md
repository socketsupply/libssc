`libssc` Developers Guide
=========================

## 0. Prerequisites

- `gcc(1)` or `clang(1)`
- `bash(1)`
- `indent(1)` (optional)
- `make(1)` (optional)

## 1. External Usage

This document is intended for `libssc` developers working on the
internals of the library. Please see [api.md](api.md) for the
porcelain/public interfaces for integrating and using this library
in your project or application.

Please check the [LICENSE](../LICENSE) to ensure this library and its
license meet your needs.

## 2. Contributing

Contributions to `libssc` can be made with a new
[pull request](https://github.com/socketsupply/libssc/compare) opened
on this library's
[canonical repository](https://github.com/socketsupply/libssc).

If you have discovered an bug or want to open up a discussion, please
[open an issue](https://github.com/socketsupply/libssc/issues/new) on
this library's [canonical repository](https://github.com/socketsupply/libssc).

Please be sure to review the following before committing or opening a
pull request to the `libssc` project:

- [Code of Conduct](../.github/CODE_OF_CONDUCT.md)
- [Commit Format](../.github/COMMIT_FORMAT.md) (See [Commit Format Examples](../.github/COMMIT_FORMAT_EXAMPLES.md))

## 3. Coding Rules

`libssc` uses the [_FFmpeg Coding Rules_][ffmpeg-coding-rules] developer
guidelines in this project with exceptions outlined in this section. For
clarity, some rules are repeated here to give a clear context of
expectations for developers contributing to this library.

### Code Format Conventions

> TODO

#### Indentation

The following outlines indentation requirements for files in the project:

- Indent size is 2
- The TAB character is forbidden with the exceptions of `Makefile` files

### Naming Conventions

This section describes various naming conventions used in `libssc`.

#### Namespacing

All types, structs, functions, variables, and macros exported for public
usage should be namespaced with `ssc_`, `SSC`, or `SSC_` depending on
the defined interface.

#### Types

All exported types should be
[PascalCamelCase](https://en.wikipedia.org/wiki/Camel_case) and
prefixed with the `SSC` namespace.

**Example:**

```c
typedef unsigned char * SSCByte
```

#### Structs

All exported structs should be
[PascalCamelCase](https://en.wikipedia.org/wiki/Camel_case) and
prefixed with the `SSC` namespace.

**Example:**

```c
struct SSCBuffer {
  SSCBytes bytes;
  SSCUSize size;
};
```

#### Functions

All exported functions and preprocessor functions should be
[snake_case](https://en.wikipedia.org/wiki/Snake_case) and prefixed with
the `ssc_` namespace.

**Example:**

```c
#define ssc_buffer(value) (SSCBuffer) (value)
```

```c
SSC_EXPORT const SSCResult
ssc_buffer_compare (const SSCBuffer self, const SSCBuffer right);
```

#### Variables

All globally (`static`) exported, externally (`extern`) linked, or
preprocessor macro variables should be
[snake_case](https://en.wikipedia.org/wiki/Snake_case) and prefixed with the
`ssc_` namespace.

**Example:**

```c
static SSCBoolean ssc_some_boolean = SSC_FALSE;
```

```c
extern SSCString *ssc_some_extern_string = 0;
```


```c
#define ssc_argc ssc_init_argc
#define ssc_argv ssc_init_argv
```

#### Preprocessor Macros

All preprocessor macros should be
[SCREAMING_SNAKE_CASE](https://en.wikipedia.org/wiki/Snake_case) and prefixed
with the `SSC_` namespace.

**Example:**

```c
#define SSC_VSNPRINTF vsnprintf
```

```c
#define SSC_PP_STRING(value) SSC_PP_STRINGX(value)
#define SSC_PP_STRINGX(value) #value
```

## 4. Development

> TODO

### Program Crashes

> TODO

#### Ubuntu

> TODO

### Debugging

> TODO

#### Apport

> TODO

#### GDB

> TODO

## 5. Tests

Tests are single context executables that emit
[TAP](https://testanything.org/) output. Tests make use of a self hosted
[`<ssc/test.h>`](../include/ssc/test.h) header file that provides
various macros and functions for making assertions that output TAP
compliant logs.

### Running Tests

The runner for each test can be invoke with a `make` target from the
root of the repository.

```sh
make tests/$TARGET
```

where `$TARGET` is the test to run which corresponds to a single `.c`
file in the `tests/` directory.

**Example:**

_Run `string` and `uri` tests:_

```sh
make tests/string tests/uri
```

_Run many tests with brace expansion:_

```sh
make tests/{string,ipc,uri,error}
```

_All tests can be run by simply invoking:_

```sh
make tests
```

### `<ssc/test.h>` API

This section describes the C API exposed by the `<ssc/test.h>`

#### `test(name, expected)`

> A simple TAP test runner context.

* `name` The name of the test context
* `expected` The expected number of passed tests. `0` means there is no
    expected count.

**Example:**

```c
#include <ssc/test.h>

test("a simple test", 2) {
  assert(1 + 1 == 2);
  assert_equal(2, 2);
  assert_not_equal(2, 3);
}
```

_Output:_

```sh
TAP version 14
# a simple test
1..3
ok 1 - 1 + 1 == 2
ok 2 - 2 equals 2
ok 3 - 2 not equals 3
```

#### `xtest(name, expected)`

> A simple macro to skip tests instead of running them marked by the leading
> `x` character in `test(...)`

**Example:**

```c
#include <ssc/test.h>

xtest("a simple skipped test", 3) {
  assert(1 + 1 == 2);
  assert_equal(2, 2);
  assert_not_equal(2, 3);
}
```

_Output:_

```sh
TAP version 14
# a simple skipped test
1..0
```

#### `assert(condition, ...)`

> A simple assertion that emits `ok ...` or `not ok ...`

**Example:**

```c
assert(1 + 1 == 3);
assert(1 != 2);
```

#### `assert_ok(condition, ...)`

> A simple assertion that emits `ok ...` or `not ok ...` along with a caught
> error that is printed as a TAP error

**Example:**

```c
#include <ssc/test.h>

test("error", 0) {
  assert_ok(ssc_throw(SSC_ERROR, "ooops"));
}
```

_Output:_

```sh
TAP version 14
# error
ok 1 (SSCResult) (SSC_OK)
not ok 1 - ssc_error_throw( SSC_ERROR, "ooops", (SSCString)("error.c"), (SSCUSize) (35), (SSCString)(__PRETTY_FUNCTION__) ) [runner (error.c:35)]
  ---
  message: (runner): ooops
  severity: fail
  at:
    file: error.c
    line: 35
  ---
1..2
# tests 2
# fail 1
# pass 1
```

#### `assert_notok(condition, ...)`

> A simple negated assertion that emits `ok ...` or `not ok ...` along with
> a caught error that is printed as a TAP error

**Example:**

```c
#include <ssc/test.h>

test("error", 0) {
  assert_notok(ssc_throw(SSC_ERROR, "oops"));
}
```

_Output:_

```sh
TAP version 14
# error
ok 1 - ssc_error_throw( SSC_ERROR, "oops", (SSCString)("error.c"), (SSCUSize) (35), (SSCString)(__PRETTY_FUNCTION__) )
not ok 2 - (SSCResult) (SSC_OK) [runner (error.c:36)]
  ---
  message: (runner): oops
  severity: fail
  at:
    file: error.c
    line: 35
  ---
1..2
# tests 2
# fail 1
# pass 1
```

#### `assert_equal(left, right, ...)`

> A simple assertion that emits `ok ...` or `not ok ...` based on the given
> `left` and `right` values inequality being true.

**Example:**

```c
test("error", 0) {
  assert_equal(1, 1);
  assert_equal(2, 2);
}
```

#### `assert_not_equal(left, right, ...)`

> A simple assertion that emits `ok ...` or `not ok ...` based on the given
> `left` and `right` values equality being true.

**Example:**

```c
test("error", 0) {
  assert_not_equal(1, 2);
  assert_not_equal(2, 3);
}
```

#### `ok(format, ...)`

> Simple `ok()` emission for a passed test.

**Example:**

```c
test("ok", 0) {
  ok("a test passed");
}
```

#### `notok(format, ...)`

> Simple `notok()` emission for a failed test.

**Example:**

```c
test("notok", 0) {
  notok("a test failed");
}
```

#### `okskip(format, ...)`

> Simple skipped `ok()` with '#SKIP' emission for a pending test.

**Example:**

```c
test("okskip", 0) {
  okskip("a skipped test assertion");
}
```

#### `notokskip(format, ...)`

> Simple skipped `notok()` with '#SKIP' emission for a pending test.

**Example:**

```c
test("okskip", 0) {
  notokskip("a skipped failing test assertion");
}
```

#### `oktodo(format, ...)`

> Simple skipped `ok()` with '#TODO' emission for a pending test.

**Example:**

```c
test("oktodo", 0) {
  oktodo("a pending test assertion marked as TODO");
}
```

#### `notoktodo(format, ...)`

> Simple skipped `notok()` with '#TODO' emission for a pending test.

**Example:**

```c
test("oktodo", 0) {
  notoktodo("a pending failed test assertion marked as TODO");
}
```


[ffmpeg-coding-rules]: https://ffmpeg.org/developer.html#Coding-Rules-1
