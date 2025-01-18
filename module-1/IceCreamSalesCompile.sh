rm *.out
gcc create_test_train_dataset.c -I ../ml-framework/include -L ../ml-framework/lib -l ml-framework -o create_test_train_dataset.out -Wall
gcc train_it.c -I ../ml-framework/include -L ../ml-framework/lib -l ml-framework -o train_it.out -Wall
gcc test_it.c -I ../ml-framework/include -L ../ml-framework/lib -l ml-framework -o test_it.out -Wall
gcc score_it.c -I ../ml-framework/include -L ../ml-framework/lib -l ml-framework -o score_it.out -Wall
#----------Here IceCreamSales Specific Commands
./create_test_train_dataset.out IceCreamSales/IceCreamSales.csv IceCreamSales/test.csv IceCreamSales/train.csv 20
./train_it.out IceCreamSales/train.csv 0.0001 IceCreamSales/history.csv 100 IceCreamSales/model.csv IceCreamSales/graph.csv 1500000
./test_it.out IceCreamSales/test.csv IceCreamSales/model.csv IceCreamSales/result.csv
./score_it.out IceCreamSales/result.csv
