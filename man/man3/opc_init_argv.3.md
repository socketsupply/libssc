opc_init_argv(3) -- Operator Framework Client Library
=====================================================

## SYNOPSIS

  `#include <opc/opc.h>`

  `const char **opc_init_argv();`

## DESCRIPTION

Returns the initialized arguments vector pointer given to `opc_init`()
or `opc_init_library`().

## RETURN VALUE

A pointer to the argument vector. This value be `NULL` if `opc_init`()
or `opc_init_library`() was not called.

## SEE ALSO

  `opc_init_argc`(3)
  `opc_init_library`(3)
  `opc_init`(3)
  `libopc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libopc/issues>

## LICENSE

MIT
