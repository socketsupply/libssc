ssc_init_argv(3) -- Socket SDK Client Library
=====================================================

## SYNOPSIS

  `#include <ssc/ssc.h>`

  `const char **ssc_init_argv();`

## DESCRIPTION

Returns the initialized arguments vector pointer given to `ssc_init`()
or `ssc_init_library`().

## RETURN VALUE

A pointer to the argument vector. This value be `NULL` if `ssc_init`()
or `ssc_init_library`() was not called.

## SEE ALSO

  `ssc_init_argc`(3)
  `ssc_init_library`(3)
  `ssc_init`(3)
  `libssc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libssc/issues>

## LICENSE

MIT
