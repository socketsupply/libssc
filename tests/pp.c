#include <opc/test.h>

#define from_macro(...) OPC_PP_VARG_COUNT(__VA_ARGS__)

test("pp", 0) {
  assert(0 == OPC_PP_VARG_COUNT());
  assert(1 == OPC_PP_VARG_COUNT(1));
  assert(2 == OPC_PP_VARG_COUNT(1, 2));
  assert(3 == OPC_PP_VARG_COUNT(1, 2, 3));
  assert(4 == OPC_PP_VARG_COUNT(1, 2, 3, 4));
  assert(5 == OPC_PP_VARG_COUNT(1, 2, 3, 4, 5));

  assert_equal(0, from_macro());
  assert_equal(1, from_macro(1));
  assert_equal(2, from_macro(1, 2));
  assert_equal(3, from_macro(1, 2, 3));
  assert_equal(4, from_macro(1, 2, 3, 4));
  assert_equal(5, from_macro(1, 2, 3, 4, 5));

  assert_equal(2, from_macro("foo", ("foo", 123)));

  // defects
  assert_equal(0, OPC_PP_VARG_COUNT(("a", "b")));
  assert_equal(0, OPC_PP_VARG_COUNT(("x", "y", "z")));
  assert_equal(0, from_macro((1, 2)));
  assert_equal(0, from_macro((1, 2, 3)));
}
