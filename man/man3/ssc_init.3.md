ssc_init(3) -- Socket SDK Client Library
================================================

## SYNOPSIS

  `#include <ssc/ssc.h>`

  `void ssc_init(int argc, const char **argv);`
  `SSCInitState ssc_init_state();`
  `const char **ssc_init_argv();`
  `const int ssc_init_argc();`

  `#include <stdio.h>`

  `void ssc_init_library(void *stdin, void *stdout, void *stderr, int argc, const char **argv);`

## DESCRIPTION

The functions in the `ssc_init`() family initialize the `libssc` library and
make various initialization data available to callers at runtime such as
the `argc` and `argv` variables given to the `main`() function.

The `ssc_init`() function initializes the `libssc` library with command line
arguments suitable for custom configuration provided by the shell caller.
The default `stdin`, `stdout`, and `stderr` file stream pointers are used.
Callers who want to use custom file stream pointers should call
`ssc_init_library()` directly instead.

## RETURN VALUE

The `ssc_init`() function does not return a value.

## EXAMPLES

  ```c
  #include <ssc/ssc.h>

  int main (int argc, const char **argv) {
    ssc_init(argc, argv);
    return 0;
  }
  ```

## NOTES

Consumers of the `libssc` library should call the `ssc_init`() function from the
`main`() function (or equivalent) before using the library.

## SEE ALSO

  `ssc_init_library`(3)
  `ssc_init_state`(3)
  `ssc_init_argc`(3)
  `ssc_init_argv`(3)
  `libssc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libssc/issues>

## LICENSE

MIT
