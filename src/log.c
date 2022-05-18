/**
 * `libssc` - Socket SDK Client Library
 *
 * This file is part of libssc.
 *
 * MIT License
 *
 * Copyright (c) 2022 Socket Supply Co.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#include <ssc/ssc.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "internal.h"

#define RED_LABEL_FORMAT "[\x1B[31m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define GREEN_LABEL_FORMAT "[\x1B[32m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define YELLOW_LABEL_FORMAT "[\x1B[33m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define BLUE_LABEL_FORMAT "[\x1B[34m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define MAGENTA_LABEL_FORMAT "[\x1B[35m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define CYAN_LABEL_FORMAT "[\x1B[36m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define WHITE_LABEL_FORMAT "[\x1B[37m%s\x1B[0m]: " SSC_LOG_LINE_FORMAT
#define PLAIN_LABEL_FORMAT "[%s]: " SSC_LOG_LINE_FORMAT

// clang-format off
static SSCString log_level_strings[] = {
  "SSC_LOG_LEVEL_EMERGENCY",
  "SSC_LOG_LEVEL_ALERT",
  "SSC_LOG_LEVEL_CRITICAL",
  "SSC_LOG_LEVEL_ERROR",
  "SSC_LOG_LEVEL_WARNING",
  "SSC_LOG_LEVEL_NOTICE",
  "SSC_LOG_LEVEL_INFO",
  "SSC_LOG_LEVEL_DEBUG"
};

static SSCString log_level_names[] = {
  "EMERG",
  "ALERT",
  "CRIT",
  "ERR",
  "WARNING",
  "NOTICE",
  "INFO",
  "DEBUG"
};

static SSCString log_level_formats[] = {
  RED_LABEL_FORMAT, // EMERG
  RED_LABEL_FORMAT, // ALERT
  RED_LABEL_FORMAT, // CRIT
  RED_LABEL_FORMAT, // ERR
  YELLOW_LABEL_FORMAT, // WARNING
  MAGENTA_LABEL_FORMAT, // NOTICE
  CYAN_LABEL_FORMAT, // INFO
  WHITE_LABEL_FORMAT // DEBUG
};

// @TODO(jwerle): use this
static SSCSize log_level_clocks[] = {
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

#ifdef SSC_LOG_LEVEL_DEFAULT
static SSCLogLevel log_level = SSC_LOG_LEVEL_DEFAULT;
#else
static SSCLogLevel log_level = SSC_LOG_LEVEL_INFO;
#endif

static void *file_stream_pointer = 0;
static SSCBoolean colors_enabled = true;

#define LOG(location, line, function, label_format, label)                     \
  if (file_stream_pointer != 0) {                                              \
    va_list args;                                                              \
    va_start(args, format);                                                    \
                                                                               \
    if (colors_enabled) {                                                      \
      SSC_FPRINTF(                                                             \
        file_stream_pointer, label_format, label, location, line, function     \
      );                                                                       \
    } else {                                                                   \
      SSC_FPRINTF(                                                             \
        file_stream_pointer,                                                   \
        PLAIN_LABEL_FORMAT,                                                    \
        label,                                                                 \
        location,                                                              \
        line,                                                                  \
        function                                                               \
      );                                                                       \
    }                                                                          \
                                                                               \
    SSC_VFPRINTF(file_stream_pointer, format, args);                           \
                                                                               \
    va_end(args);                                                              \
  }

void
ssc_log_set_level (const SSCLogLevel level) {
  log_level = level;
}

const SSCLogLevel
ssc_log_get_level () {
  return log_level;
}

const SSCString
ssc_log_get_level_string () {
  return log_level_strings[log_level];
}

const SSCString
ssc_log_get_level_name () {
  return log_level_strings[log_level];
}

void
ssc_log_set_file_stream_pointer (void *pointer) {
  file_stream_pointer = pointer;
#ifndef _WIN32
  if (isatty(0) == 0) {
    //colors_enabled = false;
  }
#endif
}

void
ssc_log_enable_colors () {
  colors_enabled = true;
}

void
ssc_log_disable_colors () {
  colors_enabled = false;
}

void
ssc_log (
  const SSCLogLevel level,
  const SSCString location,
  const SSCUSize line,
  const SSCString function,
  const SSCString format,
  ...
) {
#ifdef __ANDROID__
#  error TODO
#else
  // NOLINTNEXTLINE
  LOG(
    location, line, function, log_level_formats[level], log_level_names[level]
  );

  SSC_FPRINTF(file_stream_pointer, "\n");
#endif
}
