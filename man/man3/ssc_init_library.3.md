ssc_init_library(3) -- Socket SDK Client Library
========================================================

## SYNOPSIS

  `#include <ssc/ssc.h>`

  `void ssc_init_library(void *stdin, void *stdout, void *stderr, int argc, const char **argv);`

## DESCRIPTION

Initializes the `libssc` library with command line arguments suitable for
custom configuration provided by the shell caller. `stdin`, `stdout`,
and `stderr` should be opaque `FILE` pointers suitable for the
`fprintf`() family of functions.

## RETURN VALUE

The `ssc_init_library`() function does not return a value.

## EXAMPLES

  ```c
  #include <ssc/ssc.h>
  #include <stdio.h>

  int main (int argc, const char **argv) {
    ssc_init_library(stdin, stdout, stderr, argc, argv);
    return 0;
  }
  ```

## NOTES

Consumers of the `libssc` library should call the `ssc_init`() function from the
`main`() function (or equivalent) before using the library.

## SEE ALSO

  `ssc_init`(3)
  `libssc`(3)
  `stdio`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libssc/issues>

## LICENSE

MIT
