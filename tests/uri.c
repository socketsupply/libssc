#include "./test.h"

unsigned char stack[4096] = { 0 };

#define EXPECTED "betty%20aime%20le%20fromage%20fran%C3%A7ais"

test("uri", 4) {
  OPCBuffer expected = opc_buffer_from_string(EXPECTED);
  OPCBuffer memory = opc_buffer_from(stack);
  OPCBuffer output = opc_buffer_slice(&memory, 0, 64);
  OPCBuffer input = opc_buffer_slice(&memory, output.size, 64);
  char *string = "betty aime le fromage français";

  opc_buffer_write_string(&input, opc_buffer_bytes(string), 0);

  assert(opc_uri_component_encode(&output, input) == OPC_OK);
  assert(opc_uri_component_decode(&output, output) == OPC_OK);

  assert(opc_buffer_compare(output, expected) == OPC_OK);
  assert(opc_buffer_compare(output, input) == OPC_OK);
}
