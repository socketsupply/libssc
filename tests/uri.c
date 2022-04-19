#include <opc/opc.h>
#include <ok/ok.h>

int
main (void) {
  OPCBuffer output = {0};
  OPCBuffer input = opc_buffer_from_string("betty aime le fromage français");
  opc_uri_component_encode(output, input);
  return 0;
}
