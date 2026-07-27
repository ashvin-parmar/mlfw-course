#ifndef __MLFW_VEC_DOUBLE__
#define __MLFW_VEC_DOUBLE__

struct __mlfw_column_vec_double;
typedef struct __mlfw_column_vec_double mlfw_column_vec_double;
struct __mlfw_row_vec_double;
typedef struct __mlfw_row_vec_double mlfw_row_vec_double;

//For Column Vector
mlfw_column_vec_double * mlfw_column_vec_double_create_new(dimension_t size);
void mlfw_column_vec_double_destroy(mlfw_column_vec_double *vector);
double mlfw_column_vec_double_get(mlfw_column_vec_double *vector,index_t index);
void mlfw_column_vec_double_set(mlfw_column_vec_double *vector,index_t index,double value);
mlfw_column_vec_double *mlfw_column_vec_double_create_new_filled(dimension_t size,double value,mlfw_column_vec_double *vector);
mlfw_row_vec_double * mlfw_column_vec_double_transpose(mlfw_column_vec_double *vector,mlfw_row_vec_double *row_vector);
dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector);
double mlfw_column_vec_double_get_mean(mlfw_column_vec_double *vector);
void mlfw_column_vec_double_to_csv(mlfw_column_vec_double *vector,char *csv_filename,mlfw_row_vec_string *header);
mlfw_column_vec_double * mlfw_column_vec_double_from_csv(char *csv_filename,mlfw_column_vec_double *vector,mlfw_row_vec_string **header);
void mlfw_column_vec_double_copy(mlfw_column_vec_double *source,mlfw_column_vec_double *target,index_t source_start_index,index_t source_end_index,index_t target_start_index);

//For Rows Vector
mlfw_row_vec_double * mlfw_row_vec_double_create_new(dimension_t size);
void mlfw_row_vec_double_destroy(mlfw_row_vec_double *vector);
double mlfw_row_vec_double_get(mlfw_row_vec_double *vector,index_t index);
void mlfw_row_vec_double_set(mlfw_row_vec_double *vector,index_t index,double value);
mlfw_row_vec_double *mlfw_row_vec_double_create_new_filled(dimension_t size,double value,mlfw_row_vec_double *vector);
mlfw_column_vec_double * mlfw_row_vec_double_transpose(mlfw_row_vec_double *vector,mlfw_column_vec_double *column_vector);
dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector);
double mlfw_row_vec_double_get_mean(mlfw_row_vec_double *vector);
void mlfw_row_vec_double_to_csv(mlfw_row_vec_double *vector,char *csv_filename,mlfw_row_vec_string *header);
mlfw_row_vec_double * mlfw_row_vec_double_from_csv(char *csv_filename,mlfw_row_vec_double *vector,mlfw_row_vec_string **header);
void mlfw_row_vec_double_copy(mlfw_row_vec_double *source,mlfw_row_vec_double *target,index_t source_start_index,index_t source_end_index,index_t target_start_index);

#endif
