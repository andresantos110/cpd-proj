#!/bin/bash

output="res.txt"

for i in 1 2 3 4
do
	export OMP_NUM_THREADS=$i
	echo "Running with $i threads"
	echo "0"
	./life3d 1000 64 0.4 0 >> $output
	echo "1"
	./life3d 200 128 .5 1000 >> $output
	echo "2"
	./life3d 10 512 .4 0 >> $output
	echo "3"
	./life3d 3 1024 .4 100 >> $output
done
