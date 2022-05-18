#include <ssc/test.h>

test("a simple test", expected_pass_count = 3) {
  assert(1 + 1 == 2);
  assert_equal(2, 2);
  assert_not_equal(2, 3);
}
