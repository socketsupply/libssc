#include <opc/opc.h>
#include <stdarg.h>
#include <stdio.h>

#define RED_LABEL_FORMAT "[\x1B[31m%s\x1B[0m]: (%s:%d) "
#define GREEN_LABEL_FORMAT "[\x1B[32m%s\x1B[0m]: (%s:%d) "
#define YELLOW_LABEL_FORMAT "[\x1B[33m%s\x1B[0m]: (%s:%d) "
#define BLUE_LABEL_FORMAT "[\x1B[34m%s\x1B[0m]: (%s:%d) "
#define MAGENTA_LABEL_FORMAT "[\x1B[35m%s\x1B[0m]: (%s:%d) "
#define CYAN_LABEL_FORMAT "[\x1B[36m%s\x1B[0m]: (%s:%d) "
#define WHITE_LABEL_FORMAT "[\x1B[37m%s\x1B[0m]: (%s:%d) "
#define PLAIN_LABEL_FORMAT "[%s]: (%s:%d) "

// clang-format off
static OPCString log_level_strings[] = {
  "OPC_LOG_LEVEL_EMERGENCY",
  "OPC_LOG_LEVEL_ALERT",
  "OPC_LOG_LEVEL_CRITICAL",
  "OPC_LOG_LEVEL_ERROR",
  "OPC_LOG_LEVEL_WARNING",
  "OPC_LOG_LEVEL_NOTICE",
  "OPC_LOG_LEVEL_INFO",
  "OPC_LOG_LEVEL_DEBUG"
};

static OPCString log_level_names[] = {
  "EMERG",
  "ALERT",
  "CRIT",
  "ERR",
  "WARNING",
  "NOTICE",
  "INFO",
  "DEBUG"
};

static OPCString log_level_formats[] = {
  RED_LABEL_FORMAT, // EMERG
  RED_LABEL_FORMAT, // ALERT
  RED_LABEL_FORMAT, // CRIT
  RED_LABEL_FORMAT, // ERR
  YELLOW_LABEL_FORMAT, // WARNING
  MAGENTA_LABEL_FORMAT, // NOTICE
  CYAN_LABEL_FORMAT, // INFO
  WHITE_LABEL_FORMAT // DEBUG
};

static OPCSize log_level_clocks[] = {
  0, // EMERG
  0, // ALERT
  0, // CRIT
  0, // ERR
  0, // WARNING
  0, // NOTICE
  0, // INFO
  0 // DEBUG
};
// clang-format on

#ifdef OPC_LOG_LEVEL_DEFAULT
static OPCLogLevel log_level = OPC_LOG_LEVEL_DEFAULT;
#else
static OPCLogLevel log_level = OPC_LOG_LEVEL_INFO;
#endif

static void *file_stream_pointer = 0;
static OPCBoolean colors_enabled = OPC_TRUE;

#define LOG(location, label_format, label)                                     \
  if (file_stream_pointer != 0) {                                              \
    va_list args;                                                              \
    va_start(args, format);                                                    \
    if (colors_enabled) {                                                      \
      fprintf(file_stream_pointer, label_format, label, location, __LINE__);   \
    } else {                                                                   \
      fprintf(                                                                 \
        file_stream_pointer, PLAIN_LABEL_FORMAT, label, location, __LINE__     \
      );                                                                       \
    }                                                                          \
    vfprintf(file_stream_pointer, format, args);                               \
    fprintf(file_stream_pointer, "\n");                                        \
    va_end(args);                                                              \
  }

void
opc_log_set_level (const OPCLogLevel level) {
  log_level = level;
}

OPCLogLevel
opc_log_get_level () {
  return log_level;
}

OPCString
opc_log_get_level_string () {
  return log_level_strings[log_level];
}

OPCString
opc_log_get_level_name () {
  return log_level_strings[log_level];
}

void
opc_log_set_file_stream_pointer (void *pointer) {
  file_stream_pointer = pointer;
}

void
opc_log_enable_colors () {
  colors_enabled = OPC_TRUE;
}

void
opc_log_disable_colors () {
  colors_enabled = OPC_FALSE;
}

void
opc_log (
  const OPCLogLevel level,
  const OPCString location,
  const OPCString format,
  ...
) {
#ifdef __ANDROID__
#  error TODO
#else
  LOG(location, log_level_formats[level], log_level_names[level]);
#endif
}
