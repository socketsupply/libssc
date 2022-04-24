#ifndef OPC_TEST_H
#define OPC_TEST_H

#include <opc/opc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define STRINGX(value) #value
#define STRING(value) STRINGX(value)

/**
 * @TODO
 */
static int ok_count_;
static int ok_passed_;
static int ok_expected_;

/**
 * @TODO
 */
void
ok (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (NULL == format) {
    format = (const char *) "";
  }

  ok_passed_++;
  printf("ok %d - ", ++ok_count_);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

/**
 * @TODO
 */
void
notok (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (NULL == format) {
    format = (const char *) "";
  }

  ok_count_++;
  printf("not ok %d - ", ++ok_count_);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

/**
 * @TODO
 */
void
okskip (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (NULL == format) {
    format = (const char *) "";
  }

  printf("ok %d - ", ++ok_count_);
  vprintf(format, args);
  printf(" #skip");
  printf("\n");
  va_end(args);
}

/**
 * @TODO
 */
void
oktodo (const char *format, ...) {
  va_list args;

  va_start(args, format);

  if (NULL == format) {
    format = (const char *) "";
  }

  printf("not ok %d - ", ++ok_count_);
  vprintf(format, args);
  printf(" #TODO");
  printf("\n");
  va_end(args);
}

/**
 * @TODO
 */
void
ok_done (void) {
  if (0 != ok_expected_ && ok_passed_ != ok_expected_) {
    if (ok_expected_ > ok_passed_) {
      fprintf(stderr, "expected number of success conditions not met.\n");
    } else {
      fprintf(
        stderr,
        "expected number of success conditions is less than the "
        "number of given success conditions.\n"
      );
    }
    exit(1);
  }

  if (ok_expected_ == 0) {
    printf("1..%d\n", ok_count_);
  }

  printf("# tests %d\n", ok_count_);
  printf("# pass %d\n", ok_passed_);
}

/**
 * @TODO
 */
void
ok_expect (int expected) {
  ok_expected_ = expected;
}

/**
 * @TODO
 */
int
ok_expected () {
  return ok_expected_;
}

/**
 * @TODO
 */
int
ok_count () {
  return ok_count_;
}

/**
 * @TODO
 */
int
ok_passed () {
  return ok_passed_;
}

void
ok_reset () {
  ok_count_ = 0;
  ok_passed_ = 0;
  ok_expected_ = 0;
}

/**
 * @TODO
 */
#define test(name, expected)                                                   \
  void runner();                                                               \
  int main(void) {                                                             \
    printf("TAP version 14\n");                                                \
    printf("# %s\n", name);                                                    \
    if (expected > 0) {                                                        \
      printf("1..%d\n", expected);                                             \
      ok_expect(expected);                                                     \
    }                                                                          \
    runner();                                                                  \
    ok_done();                                                                 \
    if (expected > 0) {                                                        \
      return ok_expected() - ok_passed();                                      \
    }                                                                          \
    return ok_count() - ok_passed();                                           \
  }                                                                            \
  void runner()

/**
 * @TODO
 */
#define xtest(name, expected)                                                  \
  void runner();                                                               \
  int main(void) {                                                             \
    printf("TAP version 14\n");                                                \
    printf("# %s\n", name);                                                    \
    printf("1..0\n");                                                          \
    return 0;                                                                  \
  }                                                                            \
  void runner()

/**
 * @TODO
 */
#define assert(condition, ...)                                                 \
  {                                                                            \
    if ((condition)) {                                                         \
      ok(STRINGX(condition), ##__VA_ARGS__);                                   \
    } else {                                                                   \
      notok(STRING(condition) ": %s", ##__VA_ARGS__);                          \
    }                                                                          \
  }

#endif
