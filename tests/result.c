#include <opc/test.h>

#define assert_result_string(code)                                             \
  assert(opc_string_equals(STRING(code), opc_result_string(code)))

test("result", 0) {
  assert_result_string(OPC_OUT_OF_BOUNDS);
  assert_result_string(OPC_OUT_OF_MEMORY);
  assert_result_string(OPC_NULL_POINTER);
  assert_result_string(OPC_ERROR);
  assert_result_string(OPC_OK);
  assert_result_string(OPC_DETECTED);
  assert_result_string(OPC_NOT_DETECTED);
  assert_result_string(OPC_UNKNOWN);

  assert(opc_string_equals("OPC_UNKNOWN", opc_result_string(-30)));
  assert(opc_string_equals("OPC_UNKNOWN", opc_result_string(1046)));
}
