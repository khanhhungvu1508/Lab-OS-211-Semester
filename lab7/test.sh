#!/bin/bash
echo "Reading input file:"
cat input.txt
echo "Results scheduling:"
gcc sched.c queue.c -o sched -lpthread
cat input.txt | ./sched