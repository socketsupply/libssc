/**
 * `libssc` - Socket SDK Client Library
 *
 * This file is part of libssc.
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

#ifndef SSC_TEST_H
#define SSC_TEST_H

#include <ssc/ssc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__cplusplus) && !defined(SSC_CPLUSPLUS)
extern "C" {
#endif

/**
 * Tests stats
 */
static int total_test_count;
static int total_pass_count;
static int expected_pass_count;

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

  total_pass_count++;

  SSC_PRINTF("ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Simple `notok()` emission for a failed test.
 */
void
notok (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (format == 0) {
    format = (const char *) "";
  }

  SSC_PRINTF("not ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Simple skipped `ok()` with '#SKIP' emission for a pending test.
 */
void
okskip (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (format == 0) {
    format = (const char *) "";
  }

  SSC_PRINTF("ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF(" #SKIP");
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Simple skipped `notok()` with '#SKIP' emission for a pending test.
 */
void
notokskip (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (format == 0) {
    format = (const char *) "";
  }

  SSC_PRINTF("not ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF(" #SKIP");
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Simple skipped `ok()` with '#TODO' emission for a pending test.
 */
void
oktodo (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (format == 0) {
    format = (const char *) "";
  }

  SSC_PRINTF("ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF(" #TODO");
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Simple skipped `notok()` with '#TODO' emission for a pending test.
 */
void
notoktodo (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (format == 0) {
    format = (const char *) "";
  }

  SSC_PRINTF("not ok %d - ", ++total_test_count);
  // NOLINTNEXTLINE
  SSC_VPRINTF(format, args);
  SSC_PRINTF(" #TODO");
  SSC_PRINTF("\n");

  va_end(args);
}

/**
 * Marks tests suite as done.
 */
void
okdone (void) {
  int rc = 0;
  if (0 != expected_pass_count && total_pass_count != expected_pass_count) {
    if (expected_pass_count > total_pass_count) {
      SSC_FPRINTF(stderr, "expected number of success conditions not met.\n");
    } else {
      SSC_FPRINTF(
        stderr,
        "expected number of success conditions is less than the "
        "number of given success conditions.\n"
      );
    }

    rc = 1;
  } else if (total_pass_count != total_test_count) {
    rc = 1;
  }

  if (expected_pass_count == 0) {
    SSC_PRINTF("1..%d\n", total_test_count);
  }

  SSC_PRINTF("# tests %d\n", total_test_count);
  SSC_PRINTF("# fail %d\n", total_test_count - total_pass_count);
  SSC_PRINTF("# pass %d\n", total_pass_count);

  SSC_EXIT(rc);
}

/**
 * A simple TAP test runner context.
 * @param test_name The name of the test
 * @param expected_pass_count The expected number of passed tests where 0 means
 * no expectation
 */
#define test(test_name, ...)                                                   \
  void runner();                                                               \
  int main(const int argc, const char **argv) {                                \
    ssc_init(argc, argv);                                                      \
    { __VA_ARGS__; };                                                          \
    SSC_PRINTF("TAP version 14\n");                                            \
    SSC_PRINTF("# %s\n", test_name);                                           \
    if (expected_pass_count > 0) {                                             \
      SSC_PRINTF("1..%d\n", expected_pass_count);                              \
      expected_pass_count = expected_pass_count;                               \
    }                                                                          \
    runner();                                                                  \
    okdone();                                                                  \
    if (expected_pass_count > 0) {                                             \
      return expected_pass_count - total_pass_count;                           \
    }                                                                          \
    return total_test_count - total_pass_count;                                \
  }                                                                            \
  void runner()

/**
 * A simple macro to skip tests instead of running them marked by the leading
 * `x` character in `test()`
 */
#define xtest(test_name, ...)                                                  \
  void runner();                                                               \
  int main(void) {                                                             \
    SSC_PRINTF("TAP version 14\n");                                            \
    SSC_PRINTF("# %s\n", test_name);                                           \
    SSC_PRINTF("1..0\n");                                                      \
    return 0;                                                                  \
  }                                                                            \
  void runner()

/**
 * A simple assertion that emits `ok ...` or `not ok ...`
 * @param condition The condition to test
 * @param ...
 */
#define assert(condition, ...)                                                 \
  if ((condition)) {                                                           \
    ok("%s", SSC_PP_STRING(condition));                                        \
  } else {                                                                     \
    notok("%s", SSC_PP_STRING(condition));                                     \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

/**
 * A simple assertion that emits `ok ...` or `not ok ...` along with a caught
 * error that is printed as a TAP error
 * @param condition The condition to test
 */
#define assert_ok(condition, ...)                                              \
  if ((condition) == SSC_OK) {                                                 \
    ok(SSC_PP_STRING(condition)##__VA_ARGS__);                                 \
  } else {                                                                     \
    notok(                                                                     \
      "%s [%s %s]",                                                            \
      SSC_PP_STRING(condition),                                                \
      ssc_callsite_function_name(),                                            \
      ssc_callsite_file_location()                                             \
    );                                                                         \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

/**
 * A simple negated assertion that emits `ok ...` or `not ok ...` along with a
 * caught error that is printed as a TAP error
 * @param condition The condition to test
 */
#define assert_notok(condition, ...)                                           \
  if ((condition) != SSC_OK) {                                                 \
    ok(SSC_PP_STRING(condition)##__VA_ARGS__);                                 \
  } else {                                                                     \
    notok(                                                                     \
      "%s [%s %s]",                                                            \
      SSC_PP_STRING(condition),                                                \
      ssc_callsite_function_name(),                                            \
      ssc_callsite_file_location()                                             \
    );                                                                         \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
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
    ok("%s equals %s", SSC_PP_STRING(left), SSC_PP_STRING(right));             \
  } else {                                                                     \
    notok("%s not equals %s", SSC_PP_STRING(left), SSC_PP_STRING(right));      \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

/**
 * A simple assertion that emits `ok ...` or `not ok ...` based on the given
 * `left` and `right` values equality being true.
 * @param left Left operand
 * @param right Right operand
 */
#define assert_not_equal(left, right, ...)                                     \
  if ((left) != (right)) {                                                     \
    ok("%s not equals %s", SSC_PP_STRING(left), SSC_PP_STRING(right));         \
  } else {                                                                     \
    notok("%s equals %s", SSC_PP_STRING(left), SSC_PP_STRING(right));          \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

/**
 * A simple assertion that tests for a truthy `result` and emits `ok ...` or
 * `not ok ...` based on the given result being `SSC_TRUE` (`true`, `1`).
 * @param result Result to test for `SSC_TRUE`
 */
#define assert_true(result)                                                    \
  if ((result) != SSC_FALSE) {                                                 \
    ok("%s", SSC_PP_STRING(result));                                           \
  } else {                                                                     \
    notok("%s is not true", SSC_PP_STRING(result));                            \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

/**
 * A simple assertion that tests for a falsy `result` and emits `ok ...` or
 * `not ok ...` based on the given result being `SSC_FALSE` (`false`, `0`).
 * @param result Result to test for `SSC_FALSE`
 */
#define assert_false(result)                                                   \
  if ((result) == SSC_FALSE) {                                                 \
    ok("%s", SSC_PP_STRING(result));                                           \
  } else {                                                                     \
    notok("%s is not true", SSC_PP_STRING(result));                            \
    ssc_catch(err) {                                                           \
      SSC_PRINTF("  ---\n");                                                   \
      SSC_PRINTF("  message: %s\n", err.string);                               \
      SSC_PRINTF("  severity: fail\n");                                        \
      SSC_PRINTF("  at:\n");                                                   \
      SSC_PRINTF("    file: %s\n", __FILE__);                                  \
      SSC_PRINTF("    line: %d\n", __LINE__);                                  \
      SSC_PRINTF("  ---\n");                                                   \
    }                                                                          \
  }

#ifdef __cplusplus
}
#endif
#endif
