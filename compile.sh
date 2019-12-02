#!/usr/bin/env bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Run tests
./bin/TestMatrix
