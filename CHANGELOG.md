# [Unreleased]
## Added
- [ubjsc] Introduced UBJS_NO_EXPORT and UBJS_DEPRECATED macros, that should not expose
  internal methods.

- [ubjsc] issue #64: Added option for the writer to free items as early as possible
  during writing. This allows for early memory optimalization when you write
  very large primitives, and you discard them anyway after writing.

  See ubjs_writer_builder_set_primitive_free().

- [ci] Changelog.
- [ci] Uploading code coverage statistics to Coveralls, if token is provided.
- [ci] Scripts for profiling.
- [tests] issue #39: CI scripts for running stress tests.
- [tests] issue #39: Stress test for primitive reserialization.

## Changed
- [API BREAK] [ubjsc] issue #8:
  - ubjs_prmtv_get_type() got removed, use ubjs_prmtv_get_marker() instead.
  - ubjs_prmtv_is_*() got removed.
  - ubjs_parser_error_f changed parameters.
- [API BREAK] [ubjsc] issue #80: Pretty-prints for optimized containers do not contain trailing end marker,
  as for unoptimized ones.
- [tests] issue #56: Migrated entire test suite to [criterion](https://github.com/Snaipe/Criterion/).
- [tests] issue #39: Refactored folder hierarchy to separate stress (before: performance) test suites.
- [ci] Dockerfile now relies on jessie-backports debian instead of sid. Also changed structure a bit.

## Deprecated

## Removed
- [ubjsc] issue #8: Removed `ubjs_library_new_stdlib`. Use the regular library builder instead.

## Fixed
- [ci] Fix to insufficient valgrind results after upgrade to criterion. We did not check children for leaks, only main process was checked.
- [docs] issue #86: Fixed references to argtable2 and usage in tools.
- [ci] issue #86: Better valgrind integration within cmake files. Runs exactly the same tests like ctest - we have bonus tools coverage.

## Known issues
- [ubjspy] issue #8 broke ubjspy subproject and it is turned off. You can undisable it by yourself in `CMakeLists.txt`, but right now
  it is guaranteed to segfault on array/dict operations.  It will be fixed in another issue.
- [ubjsc] issue #8 broke freeing primitives early in containers. After the rewrite the setting does not propagate from the builder to arrays/objects, and effectively does not work. And the original idea is to be rethought. It will be fixed in another issue.

## Security

# Pre-0.6

For these releases, upgrade notes were maintained:

## [0.6] - 2017-02-22
### Added
- issue #69: Tests for tools
- issue #51: Option for parser to ignore noops

### Changed
- issue #73: Make code C89 compatible
- issue #76: Writer's debugging
- issue #50: Adhere to http://davidz25.blogspot.com/2011/07/writing-c-library-intro-conclusion-and.html
- issue #52: Option for parser to ignore noops

### Fixed
- issue #71: Parser debugs should not go to stdout/err, but into a callback
- issue #75: ubjs_library_builder should not be allocated dynamically

Now you build `ubjs_parser` with `ubjs_parser_builder`, and `ubjs_writer` with `ubjs_writer_builder`.
Explicit context structure and settings are removed, pass everything thru the builder!

Also `ubjs_library`'s content got hidden. Use `ubjs_library_get_*` to get anything relevant.

`ubjs_library_builder` no longer is dynamically allocated, to enable future usage on embedded environments.
Allocate it on your own, use new `ubjs_library_builder_init` initializer, fill it and build like before.

No more `ubjs_parser_builder_set_debug` that prints blindly into stderr. Use `ubjs_parser_builder_set_debug_f`
and pass it callback, to integrate all parser's debugging into your own logging system.

## [0.5] - 2017-01-14

Debugging stuff now does real work only when compiled with debugging symbols, as they impact performance a lot.
Build the library with `CMAKE_BUILD_TYPE=Debug` to have them back.

You can use HPN-s now in Python (via decimal.Decimal).

Previously introduced library initialization via ubjs_library_new() was removed, in favor of a builder pattern - ubjs_library_builder.
Use it to initialize the library.

In the future there are no plans to remove it, only to expand into new methods.

Via library builder you can choose a custom dictionary/array implementation - so called dict/array glue,
via methods ubjs_library_builder_set_glue_dict_builder() and ubjs_library_builder_set_glue_array_builder.
Ubjsc contains default glues:
- dictionary is based on doubly-linked list, keys are naive C-strings,
- arrays are based on array expanding/shrinking on demand.
keys are naive C-strings).
Watch out for their complexities:
- dictionary get/put/delete are is O(n * k)! Of course n is size of the container, k is size of key in characters,
- array get is O(1), put and delete are O(n).

For development of custom glues, you can re-use the default API test suite for both dictionary and array glues.
This is far from ideal, but this can be any help. The test suite checks basic API calls
and runs a short performance test.
See ubjsc/src/ubjs_glue_*.{c,h} and ubjsc/test/test_main_glues.c for examples.

For now, previous linkage to ptrie library is retained via ubjs-glue-dict-ptrie library, and right now it resides in same repository.
To use this glue, you need to explicitly link to the library and pass the factory to library builder.
Temporarily ubjspy also embeds ptrie glue.
The plan is to move ptrie glue to separate repository.

## [0.4] - 2016-11-09

You must initialize the library handle via ubjs_library_new() (or, if you are using defaults anyway - ubjs_library_stdlib()), and the$
ubjs_parser_new(), ubjs_writer_new() and ubjs_prmtv_*(). Thus they all have changed syntax.

ubjs_parser_new() accepts now security settings, that can partially prevent from crashing your app
when malicious input arrives.

Added basic support for high-precision numbers.

In case you run into problems while parsing, you can turn on the debugger. See ubjs_parser_settings.debug.

## [0.3] - 2016-07-28

Argtable2 and jansson libraries are no longer included nor fetched as subrepositories.
You need to get them separately, either getting binaries or building them. Especially on Windows.

Indentations were introduced in pretty-printouts.

## [0.2] - 2016-07-20
## [0.1] - 2016-07-10

[Unreleased]: https://bitbucket.org/tsieprawski/ubjsc/src
[0.6]: https://bitbucket.org/tsieprawski/ubjsc/src/51270ead5260214cb8796d051a3b1180b06db5e4/?at=0.6
[0.5]: https://bitbucket.org/tsieprawski/ubjsc/src/78bfbfa79a2ff6f70a6438c757290b5c9d0aecd0/?at=0.5
[0.4]: https://bitbucket.org/tsieprawski/ubjsc/src/15c600d1443f7acfff846a639146f78e059c50af/?at=0.4
[0.3]: https://bitbucket.org/tsieprawski/ubjsc/src/b2ded99d4d678d460e61a4339eebcdd527a2b949/?at=0.3
[0.2]: https://bitbucket.org/tsieprawski/ubjsc/src/eb0badd243f0faac3aca37491ecb99cdd20d4a8b/?at=0.2
[0.1]: https://bitbucket.org/tsieprawski/ubjsc/src/37d9702156af06b150de383549651970f297786d/?at=0.1
