# CI must pass

Continous integration will run these 2 scripts, and they must pass (aka they must both exit with 0 code):
- `./build.sh`. The code must build, and all unittests must pass.
- `./check.sh`
  # `./check-coverage.sh`. Coverage must be above 95% lines, 95% branches, 90% functions.
    Unfortunately this applies to all code, not only newly added one, but this will be adressed with next header.
  # `./check-static.sh`. All code must pass static analisys checks. See the script for details on the tools.
    This checks C, Python code and Bash scripts (especially the very self). :)
  # `./check-leaks.sh`. No memory leaks, period.

# Manual checks

- The CI scripts are not broken.
- All new code must be covered by unittests, or excluded (via `lcov` excludes) with explanation in relevant comments.
- All new comments and documentation must follow correct english. (:
- Changes must follow semantic versioning - be backwards-compatible with existing API, or must go to otherbranch.
- `README.md` must be updated with examples of usages, and upgrade guide must describe changes to API.
- Changes to API should be forward-compatible.
