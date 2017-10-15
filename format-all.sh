#!/bin/sh

find client server \( -name '*.cpp' -or -name '*.h' \) -print -exec clang-format --style=file -i {} \;
