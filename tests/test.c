#include <opc/test.h>

test("a simple test", 3) {
  assert(1 + 1 == 2);
  assert_equal(2, 2);
  assert_not_equal(2, 3);
}
