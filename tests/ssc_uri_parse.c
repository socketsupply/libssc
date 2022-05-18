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

#include <ssc/test.h>

static const SSCString HTTP_URI_SOURCE_STRING =
  "http://top.subdomain.domain.com/path/to/spaces in this path/resource"
  "?id=123"
  "#hash=value&string=a b c";

static const SSCString HTTP_URI_EXPECTED_STRING =
  "http://top.subdomain.domain.com/path/to/spaces%20in%20this%20path/resource"
  "?id=123"
  "#hash=value&string=a%20b%20c";

static const SSCString FILE_URI_SOURCE_STRING =
  "file:///folder/file.txt"
  "?query=string&number=123&key=valuev&biz-baz=baz biz"
  "#hash=string&words-with-number=$20.00 for 30%";

static const SSCString FILE_URI_EXPECTED_STRING =
  "file:///folder/file.txt"
  "?query=string&number=123&key=valuev&biz-baz=baz%20biz"
  "#hash=string&words-with-number=$20.00%20for%2030%25";

// clang-format off
static struct { SSCURI file; SSCURI http; } uris;
static struct { SSCURI file; SSCURI http; } expected;
// clang-format on

test("ssc_uri_parse(output, input)") {
  // clang-format off
  expected.file = (SSCURI) {
    .bytes = { 0 },
    .href = ssc_buffer_from_string(FILE_URI_EXPECTED_STRING),
    .protocol = ssc_buffer_from_string("file://"),
    .host = ssc_buffer_from_string(""),
    .path = ssc_buffer_from_string("/folder/file.txt"),
    .query = ssc_buffer_from_string(
      "?query=string&number=123&key=valuev&biz-baz=baz%20biz"
    ),
    .hash = ssc_buffer_from_string(
      "#hash=string&words-with-number=$20.00%20for%2030%25"
    )
  };

  expected.http = (SSCURI) {
    .bytes = { 0 },
    .href = ssc_buffer_from_string(HTTP_URI_EXPECTED_STRING),
    .protocol = ssc_buffer_from_string("http://"),
    .host = ssc_buffer_from_string("top.subdomain.domain.com"),
    .path = ssc_buffer_from_string(
      "/path/to/spaces%20in%20this%20path/resource"
    ),
    .query = ssc_buffer_from_string("?id=123"),
    .hash = ssc_buffer_from_string("#hash=value&string=a%20b%20c")
  };

  // clang-format on

  assert_ok(
    ssc_uri_parse(&uris.file, ssc_buffer_from_string(FILE_URI_SOURCE_STRING))
  );

  assert_true(ssc_buffer_equals(uris.file.href, expected.file.href));
  assert_true(ssc_buffer_equals(uris.file.protocol, expected.file.protocol));
  assert_true(ssc_buffer_equals(uris.file.host, expected.file.host));
  assert_true(ssc_buffer_equals(uris.file.path, expected.file.path));
  assert_true(ssc_buffer_equals(uris.file.query, expected.file.query));
  assert_true(ssc_buffer_equals(uris.file.hash, expected.file.hash));

  assert_true(ssc_buffer_equals(
    ssc_buffer_from_string(ssc_string(ssc_pointer(uris.file))),
    ssc_buffer_from_string(FILE_URI_EXPECTED_STRING)
  ));

  (void) HTTP_URI_SOURCE_STRING;
  (void) HTTP_URI_EXPECTED_STRING;

  assert_ok(
    ssc_uri_parse(&uris.http, ssc_buffer_from_string(HTTP_URI_SOURCE_STRING))
  );

  assert_true(ssc_buffer_equals(uris.http.href, expected.http.href));
  assert_true(ssc_buffer_equals(uris.http.protocol, expected.http.protocol));
  assert_true(ssc_buffer_equals(uris.http.host, expected.http.host));
  assert_true(ssc_buffer_equals(uris.http.path, expected.http.path));
  assert_true(ssc_buffer_equals(uris.http.query, expected.http.query));
  assert_true(ssc_buffer_equals(uris.http.hash, expected.http.hash));

  assert_true(ssc_buffer_equals(
    ssc_buffer_from_string(ssc_string(ssc_pointer(uris.http))),
    ssc_buffer_from_string(HTTP_URI_EXPECTED_STRING)
  ));
}
