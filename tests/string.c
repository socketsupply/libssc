#include <opc/test.h>

test("string", 0) {
  assert(opc_string_size(opc_string("hello")) == 5);
  assert(opc_string_size(opc_string("world")) == 5);
  assert(opc_string_size(opc_string("h")) == 1);
  assert(opc_string_size(opc_string("")) == 0);
  assert(opc_string_compare(opc_string("hello"), opc_string("hello")) == 0);
  assert(opc_string_compare(opc_string("hello"), opc_string("world")) == -1);
  assert(opc_string_compare(opc_string("world"), opc_string("hello")) == 1);

  assert_equal(
    0,
    opc_string_compare_with_size(
      opc_string("hello world"), 5, opc_string("hello moon"), 5
    )
  );

  assert_equal(
    0,
    opc_string_compare_with_size(
      opc_string_slice(opc_string("hello world"), 6),
      5,
      opc_string_slice(opc_string("goodbye world"), 8),
      5
    )
  );
}
