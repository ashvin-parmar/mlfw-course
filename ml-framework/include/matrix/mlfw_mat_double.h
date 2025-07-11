#ifndef __MLFW_MAT_DOUBLE__
#define __MLFW_MAT_DOUBLE__
struct __mlfw_mat_double;
typedef struct  __mlfw_mat_double mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows,dimension_t columns);
mlfw_mat_double * mlfw_mat_double_create_new_filled(dimension_t rows,dimension_t columns,double value,mlfw_mat_double *matrix);

void mlfw_mat_double_destroy(mlfw_mat_double *matrix);
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name,mlfw_mat_double *matrix,mlfw_row_vec_string **header);
void mlfw_mat_double_to_csv(mlfw_mat_double *matrix,const char *csv_file_name,mlfw_row_vec_string *header);
double mlfw_mat_double_get(mlfw_mat_double *matrix,index_t row,index_t column);
void mlfw_mat_double_set(mlfw_mat_double *matrix,index_t row,index_t column,double value);
void mlfw_mat_double_get_dimension(mlfw_mat_double *matrix,dimension_t *rows,dimension_t *columns);


void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index);
mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t column_index,mlfw_column_vec_double *vector);
void mlfw_mat_double_fill(mlfw_mat_double *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value);
mlfw_mat_double * mlfw_mat_double_shuffle(mlfw_mat_double *matrix, uint8_t shuffle_times,mlfw_mat_double *shuffled_matrix);
mlfw_mat_double *mlfw_mat_double_transpose(mlfw_mat_double *matrix,mlfw_mat_double *matrix_t);

double mlfw_mat_double_get_minimum(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index);

double mlfw_mat_double_get_maximum(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index);
double mlfw_mat_double_get_mean(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index);

double mlfw_mat_double_get_standard_deviation(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index);

void mlfw_mat_double_get_training_testing_data(const char *csv_file_name,mlfw_mat_double **training_matrix,mlfw_mat_double **testing_matrix,uint8_t testing_data_percentage);

#endif
