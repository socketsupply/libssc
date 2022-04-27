#include <opc/opc.h>

static OPCInitState init_state = OPC_INIT_NONE;
static int init_argc = 0;
static const char **init_argv = 0;

OPCInitState
opc_init_state () {
  return init_state;
}

void
opc_init (const int argc, const char **argv) {
  if (init_state == OPC_INIT_NONE) {
    init_state = OPC_INIT_PENDING;
    init_argc = argc;
    init_argv = argv;
    opc_log_set_file_stream_pointer(stderr);
    init_state = OPC_INIT_READY;
  }
}

int
opc_init_argc () {
  return init_argc;
}

const char **
opc_init_argv () {
  return init_argv;
}
