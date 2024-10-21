gcc -c ../src/matrix/mlfw_mat_double.c -I ../include -Wall
gcc -c ../src/vector/mlfw_vec_double.c -I ../include -Wall
gcc -c ../src/operations/mlfw_operations.c -I ../include -Wall
ar rcs ../lib/libml-framework.a *.o
