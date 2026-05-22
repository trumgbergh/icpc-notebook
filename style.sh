#!/usr/bin/env bash

find library -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' -o -iname '*.cc' | xargs clang-format -i
