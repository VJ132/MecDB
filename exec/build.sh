#!/bin/bash

current_dir="$(pwd)"

gcc -Wall -Wextra -O3 "$current_dir/src/mec_engine/mec_engine.c" \
    -o "$current_dir/bin/build"
