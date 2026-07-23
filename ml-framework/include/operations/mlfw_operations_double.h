#ifndef __MLFW_OPERATION_DOUBLE__
#define __MLFW_OPERATION_DOUBLE__

//Matrix X Matrix
mlfw_mat_double * mlfw_multiply_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix);

mlfw_mat_double * mlfw_add_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix);
mlfw_mat_double * mlfw_subtract_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix);

//Vector X Matrix
mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *left_matrix,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *product_vector);


//Vector X Vector
mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *left_vector,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *diff_vector);
mlfw_column_vec_double * mlfw_multiply_double_row_vector_with_column_vector(mlfw_row_vec_double *left_vector,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *product_vector);
mlfw_column_vec_double * mlfw_multiply_double_scalar_with_column_vector(double scalar,mlfw_column_vec_double *vector,mlfw_column_vec_double *product_vector);


#endif
