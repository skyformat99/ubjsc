# CI must pass

Continuous integration will run these 2 scripts, and they must pass (aka they must both exit with 0 code):

- `./build.sh`. The code must build, and all unit tests must pass.
- `./check.sh` encapsulates 3 below
  - `./check-coverage.sh`. Coverage must be above 95% lines, 95% branches, 90% functions.
  Unfortunately this applies to all code, not only newly added one, but this will be addressed with next header.
  - `./check-static.sh`. All code must pass static analysis checks. See the script for details on the tools.
  This checks C, Python code and Bash scripts (especially the very self). :)
  - `./check-leaks.sh`. No memory leaks. Full stop.

# Manual checks

- The CI scripts are not broken.
- All new code must be covered by unit tests, or excluded (via `lcov` excludes) with explanation in relevant comments.
- All new comments and documentation must follow correct english. (:
- Changes must follow semantic versioning - be backwards-compatible with existing API, or must go to relevant spin-off branch, or plan new major version.
- `README.md` must be updated with examples of usages, and upgrade guide must describe changes to API.
- `CHANGELOG.md` must be updated with the changes in `[Unreleased]` section, in appropriate subsection.
  `[API BREAK]` must be added, if changes break existing API.
  Note that during 0.x versions, this does not neccessarily mean upping the version major.
- Changes to API should be forward-compatible. Design API to use design patterns (builders, glues etc.).
