#include <opc/opc.h>
#include <stdarg.h>

void
ipc_flush () {
  OPC_FPRINTF(stdout, "\n");
}

OPCResult
opc_ipc_vwrite (const OPCString string, va_list args) {
  if (string != 0) {
    OPC_VFPRINTF(stdout, string, args);
  }
}

OPCResult
opc_ipc_write (const OPCString string, ...) {
  va_list args;

  va_start(args, string);
  opc_ipc_vwrite(string, args);
  va_end(args);

  return OPC_OK;
}

OPCResult
opc_ipc_flush (const OPCString string, ...) {
  va_list args;

  va_start(args, string);
  opc_ipc_vwrite(string, args);
  ipc_flush();
  va_end(args);

  return OPC_OK;
}

OPCResult
opc_ipc_send (const OPCIPCSendOptions options) {
  if (options.event == 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Missing options.event");
  }

  if (options.value.size > 0 && options.value.bytes != 0) {
    return opc_ipc_write(
      "ipc://send?window=%llu&event=%s&value=%*.s\n",
      options.window,
      options.event,
      options.value.size,
      opc_string(options.value.bytes)
    );
  }

  return opc_ipc_write(
    "ipc://send?window=%llu&event=%s\n",
    options.window,
    options.event
  );
}

OPCResult
opc_ipc_request (const OPCIPCRequestOptions options) {
  return OPC_OK;
}
