#!/bin/bash

if [ ! -f ./test/doctest.h ]; then
    wget -q https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P ./test
fi

cmake .

