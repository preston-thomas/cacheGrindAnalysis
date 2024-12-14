#!/bin/bash

for block_size in 32 64 128 256; do
        echo "Block size: $block_size bytes"

        #Nested loop for assoc
        for assoc in 1 2 4 8 16; do
                echo "Block size: $block_size , assoc: $assoc"
                valgrind --tool=cachegrind --D1=4096,$assoc,$block_size --cache-sim=yes ./bs6.o input_1e4.txt

        done

        #Calculate assoc using the cache size & block size
        #Run for every block size, independent of assoc size above
        full_assoc=$((4096/block_size))
        echo "Running fully assoc for block size $block_size, fully assoc $full_assoc-way cache"
        valgrind --tool=cachegrind --D1=4096,$full_assoc,$block_size --cache-sim=yes ./bs6.o input_1e4.txt
done
