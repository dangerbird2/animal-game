#!/bin/sh
#clang format script

STYLE=Google
cd $(dirname $0)
clang-format --style=$STYLE -i  \
    ./tests/*.cc                \
    ./include/animal/*.h        \
    ./src/*.c