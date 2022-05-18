ssc_init_state(3) -- Socket SDK Client Library
======================================================

## SYNOPSIS

  `#include <ssc/ssc.h>`

  `SSCInitState ssc_init_state();`

## DESCRIPTION

Returns the current library initialization state.

## RETURN VALUE

The `ssc_init_state`() function returns an enumerated `SSCInitState`
value based on the current initialization state.

```
typedef enum {
  SSC_INIT_ERROR = -1,
  SSC_INIT_NONE = 0,
  SSC_INIT_PENDING = 1,
  SSC_INIT_READY = 2,
  SSC_INIT_UNKNOWN = SSC_MAX_ENUM
} SSCInitState;
```

## SEE ALSO

  `ssc_init`(3)
  `libssc`(3)

## REPORTING BUGS

  - <https://github.com/socketsupply/libssc/issues>

## LICENSE

MIT
