./../../../../../tools/build/create_test_train_dataset IceCreamSales.csv test.csv train.csv 20
./../../../build/train_it train.csv 0.0001 history.csv 100 trained_parameter.csv graph_data.csv 1000000
./../../../build/test_it test.csv trained_parameter.csv result.csv 
./../../../../../tools/build/r2score result.csv 
