#!/bin/bash

### This script is used to run clang-format on the source files.

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Directories
readonly INCLUDE_DIR=$DIR/include
readonly TEST_DIR=$DIR/test
readonly CLANG_FMT_DIR=$DIR/deps/clang-format

# files
readonly FMT_SH=$CLANG_FMT_DIR/fmt.sh
readonly DOT_CLANG_FORMAT=$CLANG_FMT_DIR/.clang-format

delete_file_if_exists () {
    if [ -e $1 ]; then
        rm -f $1
    fi
}

format () {
    cd $1
    delete_file_if_exists ./.clang-format
    cp $DOT_CLANG_FORMAT ./.clang-format
    bash $FMT_SH
    rm -f ./.clang-format
}

# Format the source files.
format $INCLUDE_DIR
format $TEST_DIR

