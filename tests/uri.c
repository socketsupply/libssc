#include <opc/test.h>
#include <string.h>

// includes decoded unicode characters
#define SOURCE_STRING "betty aime le fromage français"
// includes encoded unicode characters
#define EXPECTED_STRING "betty%20aime%20le%20fromage%20fran%C3%A7ais"

// static memory stack
static OPCByte stack[4096] = { 0 };

test("uri", 0) {
  const OPCString expected = opc_string(EXPECTED_STRING);
  const OPCString source = opc_string(SOURCE_STRING);

  const OPCUSize expected_size = opc_string_size(expected);
  const OPCUSize source_size = opc_string_size(source);

  OPCBuffer memory = opc_buffer_from(stack);
  OPCBuffer output = opc_buffer_slice(memory, 0, expected_size);
  OPCBuffer input = opc_buffer_slice(memory, output.size, source_size);

  // write source to input buffer
  opc_log_info("%d", input.size);
  opc_log_info("%d\n", opc_buffer_write_string(&input, source, 0));
  //assert(opc_buffer_write_string(&input, source, 0) > 0);

  // verify successful encode of input into output
  assert_ok(opc_uri_component_encode(&output, input));

  // verify output buffer matches expected
  assert_ok(opc_buffer_compare(output, opc_buffer_from_string(expected)));

  opc_log_info("%s", opc_string(output.bytes));

  // control
  assert(
    0 == strncmp(opc_string(output.bytes), EXPECTED_STRING, sizeof(EXPECTED_STRING))
  );

  // verify encoded output was decoded and equal to input
  assert_ok(opc_buffer_compare(output, input));
  assert_ok(opc_uri_component_decode(&output, output));
}
