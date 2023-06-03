#!/bin/bash

threads=(1 2 4 8 16 32 64)
duration=30

# echo "duration= $duration"
# echo "Running psum-mutex"
# for t in "${threads[@]}"; do
#     echo "Running with $t threads"
#     time ./psum-mutex "$t" "$duration"
#     echo ""
# done

echo ""
echo "------------------------------------------"
echo "Running psum-mutex-opt: use array"
for t in "${threads[@]}"; do
    echo "Running with $t threads"
    time ./psum-mutex-array "$t" "$duration"
    echo ""
done

echo ""
echo "------------------------------------------"
echo "Running psum-mutex-opt: use local variable"
for t in "${threads[@]}"; do
    echo "Running with $t threads"
    time ./psum-mutex-better "$t" "$duration"
    echo ""
done
