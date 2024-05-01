#!/bin/bash

CC=gcc
SRC=$(find tests/ -name "*.c")

for file in $SRC; do
    EXE=${file/.c/}

    if [[ $1 == "clean" ]]; then
        rm $EXE
        continue
    fi

    $CC $file -lpgn -o $EXE
    ./$EXE
done
