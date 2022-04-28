opc_init_state(3) -- Operator Framework Client Library
======================================================

## SYNOPSIS

  `#include <opc/opc.h>`

  `OPCInitState opc_init_state();`

## DESCRIPTION

Returns the current library initialization state.

## RETURN VALUE

The `opc_init_state`() function returns an enumerated `OPCInitState`
value based on the current initialization state.

```
typedef enum {
  OPC_INIT_ERROR = -1,
  OPC_INIT_NONE = 0,
  OPC_INIT_PENDING = 1,
  OPC_INIT_READY = 2,
  OPC_INIT_UNKNOWN = OPC_MAX_ENUM
} OPCInitState;
```

## SEE ALSO

  `opc_init`(3)
  `libopc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libopc/issues>

## LICENSE

MIT
