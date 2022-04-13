`libopc` Developers Guide
=========================

## 0. Prerequisites

- `gcc(1)` or `clang(1)`
- `bash(1)`
- `indent(1)` (optional)
- `make(1)` (optional)

## 1. External Usage

This document is intended for `libopc` developers working on the
internals of the library. Please see [api.md](api.md) for the
porcelain/public interfaces for integrating and using this library
in your project or application.

Please check the [LICENSE](../LICENSE) to ensure this library and its
license meet your needs.

## 2. Contributing

Contributions to `libopc` can be made with a new
[pull request](https://github.com/socketsupply/libopc/compare) opened
on this library's
[canonical repository](https://github.com/socketsupply/libopc).

If you have discovered an bug or want to open up a discussion, please
[open an issue](https://github.com/socketsupply/libopc/issues/new) on
this library's [canonical repository](https://github.com/socketsupply/libopc).

## 3. Coding Rules

`libopc` uses the [_FFmpeg Coding Rules_][ffmpeg-coding-rules] developer
guidelines in this project with exceptions outlined in this section. For
clarity, some rules are repeated here to give a clear context of
expectations for developers contributing to this library.

### Code Format Conventions

> TODO

#### Indentation

The following outlines indentation requirements for files in the project:

- Indent size is 2
- The TAB character is forbidden with the exceptions of `Makefile` files

### Naming Conventions

> TODO

[ffmpeg-coding-rules]: https://ffmpeg.org/developer.html#Coding-Rules-1
