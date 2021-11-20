make
./a.out
make gcov
make gprof
./a.out > output
python3 check.py 
