#!/bin/bash

find -name '*.cpp' -o -name '*.hh' -o -name '*.hpp' -o -name '*.h' | xargs clang-format -i

