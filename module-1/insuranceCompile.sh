rm *.out
./cmp.sh one_hot_encode.c one_hot_encode.out
./cmp.sh create_test_train_dataset.c create_test_train_dataset.out
./cmp.sh min_max_scalar.c min_max_scalar.out
./cmp.sh train_it.c train_it.out
./cmp.sh min_max_test_data_scalar.c min_max_test_data_scalar.out
./cmp.sh test_it.c test_it.out 
./cmp.sh score_it.c score_it.out
#----------Here Insurance Specific Commands
./one_hot_encode.out Insurance/insurance.csv Insurance/one_hot_encoded_insurance.csv 1,4,5 Y
./create_test_train_dataset.out Insurance/one_hot_encoded_insurance.csv Insurance/test.csv Insurance/train.csv 20
./min_max_scalar.out Insurance/train.csv Insurance/scaled_train.csv 0 11 Insurance/min_max_scalar.csv
./min_max_test_data_scalar.out Insurance/test.csv Insurance/scaled_test.csv 0 11 Insurance/min_max_scalar.csv
# over herer, change the number of arguments or skip it whatever when press enter [optional]
# remove 60000 because its optional, Use 'Enter' key for stop training
./train_it.out Insurance/scaled_train.csv 0.01 Insurance/history.csv 100 Insurance/model.csv Insurance/graph.csv 60000
./test_it.out Insurance/scaled_test.csv Insurance/model.csv Insurance/scaled_result.csv
#Opening scaled_result.csv to remove header [Do it manually]
vim Insurance/scaled_result.csv
./score_it.out Insurance/scaled_result.csv
