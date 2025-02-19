#!/bin/bash

clang-format -i "$1"
sed -i 's/^#\(include\|define\)/    #\1/' "$1"
