#!/bin/bash

for i in {1..5}; do
    folder="exo${i}"
    echo $folder
    cd $folder
    make clean
    cd ..
done