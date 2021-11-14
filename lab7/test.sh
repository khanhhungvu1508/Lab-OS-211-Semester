#!/bin/bash
printf "Reading input file:\n"
cat input.txt
printf "\nResults scheduling:\n"
gcc sched.c queue.c -o sched -lpthread
cat input.txt | ./sched
