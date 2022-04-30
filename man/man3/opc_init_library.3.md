opc_init_library(3) -- Operator Framework Client Library
========================================================

## SYNOPSIS

  `#include <opc/opc.h>`

  `void opc_init_library(void *stdin, void *stdout, void *stderr, int argc, const char **argv);`

## DESCRIPTION

Initializes the `libopc` library with command line arguments suitable for
custom configuration provided by the shell caller. `stdin`, `stdout`,
and `stderr` should be opaque `FILE` pointers suitable for the
`fprintf`() family of functions.

## RETURN VALUE

The `opc_init_library`() function does not return a value.

## EXAMPLES

  ```c
  #include <opc/opc.h>
  #include <stdio.h>

  int main (int argc, const char **argv) {
    opc_init_library(stdin, stdout, stderr, argc, argv);
    return 0;
  }
  ```

## NOTES

Consumers of the `libopc` library should call the `opc_init`() function from the
`main`() function (or equivalent) before using the library.

## SEE ALSO

  `opc_init`(3)
  `libopc`(3)
  `stdio`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libopc/issues>

## LICENSE

MIT
