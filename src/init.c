#include <opc/opc.h>

static OPCInitState init_state = OPC_INIT_NONE;

OPCInitState
opc_init_state () {
  return init_state;
}

void
opc_init () {
  if (init_state == OPC_INIT_NONE) {
    init_state = OPC_INIT_PENDING;
    opc_log_set_file_stream_pointer(stderr);
    init_state = OPC_INIT_READY;
  }
}
