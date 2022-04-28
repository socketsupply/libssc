opc_init(3) -- Operator Framework Client Library
================================================

## SYNOPSIS

  `#include <opc/opc.h>`

  `void opc_init(int argc, const char **argv);`
  `OPCInitState opc_init_state();`
  `const char **opc_init_argv();`
  `const int opc_init_argc();`

  `#include <stdio.h>`

  `void opc_init_library(void *stdin, void *stdout, void *stderr, int argc, const char **argv);`

## DESCRIPTION

The functions in the `opc_init`() family initialize the `libopc` library and
make various initialization data available to callers at runtime such as
the `argc` and `argv` variables given to the `main`() function.

The `opc_init`() function initializes the `libopc` library with command line
arguments suitable for custom configuration provided by the shell caller.
The default `stdin`, `stdout`, and `stderr` file stream pointers are used.
Callers who want to use custom file stream pointers should call
`opc_init_library()` directly instead.

## RETURN VALUE

The `opc_init`() function does not return a value.

## EXAMPLES

  ```c
  #include <opc/opc.h>

  int main (int argc, const char **argv) {
    opc_init(argc, argv);
    return 0;
  }
  ```

## NOTES

Consumers of the `libopc` library should call the `opc_init`() function from the
`main`() function (or equivalent) before using the library.

## SEE ALSO

  `opc_init_library`(3)
  `opc_init_state`(3)
  `opc_init_argc`(3)
  `opc_init_argv`(3)
  `libopc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libopc/issues>

## LICENSE

MIT
