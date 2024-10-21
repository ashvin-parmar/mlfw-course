#ifndef __MLFW_MAT_DOUBLE__
#define __MLFW_MAT_DOUBLE__
struct __mlfw_mat_double;
typedef struct  __mlfw_mat_double mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows,dimension_t columns);
void mlfw_mat_double_destroy(mlfw_mat_double *matrix);
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name);
double mlfw_mat_double_get(mlfw_mat_double *matrix,index_t row,index_t column);
void mlfw_mat_double_set(mlfw_mat_double *matrix,index_t row,index_t column,double value);
void mlfw_mat_double_get_dimension(mlfw_mat_double *matrix,dimension_t *rows,dimension_t *columns);
#endif
