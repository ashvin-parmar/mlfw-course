rm *.o
gcc -c *.c -I ./../../include
rm ./../../lib/libmatrix.a
ar rcs ./../../lib/libmatrix.a *.o
