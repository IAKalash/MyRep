gcc -c -fPIC core.c -o core.o
gcc -shared -o core.so core.o
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH