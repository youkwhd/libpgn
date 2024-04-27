#!/bin/bash

CC=gcc
SRC=$(find test/ -name "*.c")

for file in $SRC; do
    EXE=${file/.c/}

    if [[ $1 == "clean" ]]; then
        rm $EXE
        continue
    fi

    $CC $file -I. -L. -lpgn -o $EXE
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/. ./$EXE
done