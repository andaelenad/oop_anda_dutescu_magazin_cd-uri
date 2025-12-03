#!/usr/bin/bash

cppcheck \
  --enable=all \
  --inconclusive \
  --quiet \
  --suppress=missingIncludeSystem \
  --exclude=catch.hpp \
  --exclude=tests/catch.hpp \
  --exclude=ext/catch \
    --inline-suppr \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=useStlAlgorithm \
    --check-level=exhaustive \
    --error-exitcode=1


