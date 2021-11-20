#!/bin/sh
#make run analyse and check the program
make
./a.out > output
make gcov
make gprof
python3 check.py 
