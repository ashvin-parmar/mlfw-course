rm  *.o
rm ../lib/libmlfw_wrapper.a
g++ -c ../src/MLFWException.cpp -I ../include/
g++ -c ../src/matrix/*.cpp -I ../include/ -I ../../../ml-framework/include/ -L ../../../ml-framework/lib/ -lml-framework
g++ -c ../src/vector/*.cpp -I ../include -I ../../../ml-framework/include -L ../../../ml-framework/lib/ -lml-framework
ar rcs ../lib/libmlfw_wrapper.a *.o
