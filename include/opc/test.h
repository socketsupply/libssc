/**
 * `libopc` - Operator Framework Client Library
 *
 * This file is part of libopc.
 *
 * MIT License
 *
 * Copyright (c) 2022 Socket Supply Co.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#ifndef OPC_TEST_H
#define OPC_TEST_H

#include <opc/opc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Tests stats
 */
static int ok_count;
static int ok_passed;
static int ok_expected;

/**
 * Simple `ok()` emission for a passed test.
 */
void
ok (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  ok_passed++;
  printf("ok %d - ", ++ok_count);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

/**
 * Simple `notok()` emission for a failed test.
 */
void
notok (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  printf("not ok %d - ", ++ok_count);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

/**
 * Simple skipped `ok()` with '#SKIP' emission for a pending test.
 */
void
okskip (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  printf("ok %d - ", ++ok_count);
  vprintf(format, args);
  printf(" #SKIP");
  printf("\n");
  va_end(args);
}

/**
 * Simple skipped `notok()` with '#SKIP' emission for a pending test.
 */
void
notokskip (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  printf("not ok %d - ", ++ok_count);
  vprintf(format, args);
  printf(" #SKIP");
  printf("\n");
  va_end(args);
}

/**
 * Simple skipped `ok()` with '#TODO' emission for a pending test.
 */
void
oktodo (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  printf("ok %d - ", ++ok_count);
  vprintf(format, args);
  printf(" #TODO");
  printf("\n");
  va_end(args);
}


/**
 * Simple skipped `notok()` with '#TODO' emission for a pending test.
 */
void
notoktodo (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (!format) {
    format = (const char *) "";
  }

  printf("not ok %d - ", ++ok_count);
  vprintf(format, args);
  printf(" #TODO");
  printf("\n");
  va_end(args);
}

/**
 * Marks tests suite as done.
 */
void
okdone (void) {
  int rc = 0;
  if (0 != ok_expected && ok_passed != ok_expected) {
    if (ok_expected > ok_passed) {
      fprintf(stderr, "expected number of success conditions not met.\n");
    } else {
      fprintf(
        stderr,
        "expected number of success conditions is less than the "
        "number of given success conditions.\n"
      );
    }

    rc = 1;
  }

  if (ok_expected == 0) {
    printf("1..%d\n", ok_count);
  }

  printf("# tests %d\n", ok_count);
  printf("# fail %d\n", ok_count - ok_passed);
  printf("# pass %d\n", ok_passed);

  exit(rc);
}

/**
 * A simple TAP test runner context.
 * @param test_name The name of the test
 * @param expected_pass_count The expected number of passed tests where 0 means
 * no expectation
 */
#define test(test_name, expected_pass_count)                                   \
  void runner(                                                                 \
    const char *_test_name, const unsigned int _expected_pass_count            \
  );                                                                           \
  int main(const int argc, const char **argv) {                                \
    opc_init(argc, argv);                                                      \
    printf("TAP version 14\n");                                                \
    printf("# %s\n", test_name);                                               \
    if (expected_pass_count > 0) {                                             \
      printf("1..%d\n", expected_pass_count);                                  \
      ok_expected = expected_pass_count;                                       \
    }                                                                          \
    runner(test_name, expected_pass_count);                                    \
    okdone();                                                                  \
    if (expected_pass_count > 0) {                                             \
      return ok_expected - ok_passed;                                          \
    }                                                                          \
    return ok_count - ok_passed;                                               \
  }                                                                            \
  void runner(const char *_test_name, const unsigned int _expected_pass_count)

/**
 * A simple macro to skip tests instead of running them marked by the leading
 * `x` character in `test()`
 */
#define xtest(test_name, expected_pass_count)                                  \
  void runner(                                                                 \
    const char *_test_name, const unsigned int _expected_pass_count            \
  );                                                                           \
  int main(void) {                                                             \
    printf("TAP version 14\n");                                                \
    printf("# %s\n", test_name);                                               \
    printf("1..0\n");                                                          \
    return 0;                                                                  \
  }                                                                            \
  void runner(const char *_test_name, const unsigned int _expected_pass_count)

/**
 * A simple assertion that emits `ok ...` or `not ok ...`
 * @param condition The condition to test
 * @param ...
 */
#define assert(condition, ...)                                                 \
  if ((condition)) {                                                           \
    ok("%s", OPC_PP_STRINGX(condition));                                       \
  } else {                                                                     \
    notok("%s", OPC_PP_STRINGX(condition));                                    \
  }

/**
 * A simple assertion that emits `ok ...` or `not ok ...` along with a caught
 * error that is printed as a TAP error
 * @param condition The condition to test
 */
#define assert_ok(condition, ...)                                              \
  if ((condition) == OPC_OK) {                                                 \
    ok(OPC_PP_STRINGX(condition), ##__VA_ARGS__);                              \
  } else {                                                                     \
    opc_catch(err) {                                                           \
      notok(                                                                   \
        "%s [%s %s]",                                                          \
        OPC_PP_STRINGX(condition),                                             \
        opc_callsite_function_name(),                                          \
        opc_callsite_file_location()                                           \
      );                                                                       \
      printf("  ---\n");                                                       \
      printf("  message: (%s): %s\n", err.function, err.message);              \
      printf("  severity: fail\n");                                            \
      printf("  at:\n");                                                       \
      printf("    file: %s\n", err.location);                                  \
      printf("    line: %llu\n", err.line);                                    \
      printf("  ---\n");                                                       \
    }                                                                          \
  }

/**
 * A simple negated assertion that emits `ok ...` or `not ok ...` along with a
 * caught error that is printed as a TAP error
 * @param condition The condition to test
 */
#define assert_notok(condition, ...)                                           \
  if ((condition) != OPC_OK) {                                                 \
    ok(OPC_PP_STRINGX(condition), ##__VA_ARGS__);                              \
  } else {                                                                     \
    opc_catch(err) {                                                           \
      notok(                                                                   \
        "%s [%s %s]",                                                          \
        OPC_PP_STRINGX(condition),                                             \
        opc_callsite_function_name(),                                          \
        opc_callsite_file_location()                                           \
      );                                                                       \
      printf("  ---\n");                                                       \
      printf("  message: (%s): %s\n", err.function, err.message);              \
      printf("  severity: fail\n");                                            \
      printf("  at:\n");                                                       \
      printf("    file: %s\n", err.location);                                  \
      printf("    line: %llu\n", err.line);                                    \
      printf("  ---\n");                                                       \
    }                                                                          \
  }

/**
 * A simple assertion that emits `ok ...` or `not ok ...` based on the given
 * `left` and `right` values inequality being true.
 * @param left Left operand
 * @param right Right operand
 */
#define assert_equal(left, right, ...)                                         \
  if ((left) == (right)) {                                                     \
    ok("%s equals %s", OPC_PP_STRINGX(left), OPC_PP_STRINGX(right));           \
  } else {                                                                     \
    notok("%s not equals %s", OPC_PP_STRINGX(left), OPC_PP_STRINGX(right));    \
  }

/**
 * A simple assertion that emits `ok ...` or `not ok ...` based on the given
 * `left` and `right` values equality being true.
 * @param left Left operand
 * @param right Right operand
 */
#define assert_not_equal(left, right, ...)                                     \
  if ((left) != (right)) {                                                     \
    ok("%s not equals %s", OPC_PP_STRINGX(left), OPC_PP_STRINGX(right));       \
  } else {                                                                     \
    notok("%s equals %s", OPC_PP_STRINGX(left), OPC_PP_STRINGX(right));        \
  }

#ifdef __cplusplus
}
#endif
#endif
