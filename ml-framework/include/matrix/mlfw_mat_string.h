#ifndef __MLFW_MAT_STRING__
#define __MLFW_MAT_STRING__
struct __mlfw_mat_string;
typedef struct  __mlfw_mat_string mlfw_mat_string;
mlfw_mat_string * mlfw_mat_string_create_new(dimension_t rows,dimension_t columns);

void mlfw_mat_string_destroy(mlfw_mat_string *matrix);
mlfw_mat_string * mlfw_mat_string_from_csv(const char *csv_file_name,mlfw_mat_string *matrix,mlfw_row_vec_string **header);
void mlfw_mat_string_to_csv(mlfw_mat_string *matrix,const char *csv_file_name,mlfw_row_vec_string *header);
void mlfw_mat_string_get(mlfw_mat_string *matrix,index_t row,index_t column,char **value);
void mlfw_mat_string_set(mlfw_mat_string *matrix,index_t row,index_t column,const char *value);
void mlfw_mat_string_get_dimension(mlfw_mat_string *matrix,dimension_t *rows,dimension_t *columns);
mlfw_mat_string * mlfw_mat_string_transpose(mlfw_mat_string *matrix,mlfw_mat_string *transposed_matrix);

void mlfw_mat_string_copy(mlfw_mat_string *target,mlfw_mat_string *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index);
mlfw_mat_string * mlfw_mat_string_shuffle(mlfw_mat_string *matrix, uint8_t shuffle_times,mlfw_mat_string *shuffled_matrix);

/*
mlfw_column_vec_string * mlfw_mat_string_create_column_vec(mlfw_mat_string *matrix,index_t column_index);
void mlfw_mat_string_fill(mlfw_mat_string *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,string value);
mlfw_mat_string *mlfw_mat_string_transpose(mlfw_mat_string *matrix);
*/
#endif
