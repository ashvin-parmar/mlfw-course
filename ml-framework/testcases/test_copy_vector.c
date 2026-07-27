#include <stdio.h>
#include <mlfw_vector.h>
/**
 * Author: Ashvin
 * Date: 2026-07-27
 * Description: 
 */
void print_column_vector(mlfw_column_vec_double *vector)
{
index_t i;
dimension_t size;
if(vector==NULL) return;

size=mlfw_column_vec_double_get_size(vector);
for(i=0;i<size;++i)
{
	printf("%10.2lf\n",mlfw_column_vec_double_get(vector,i));
}
}

int main() {
	mlfw_column_vec_double *row_vector,*copy_vector;
	dimension_t rvec_size;
	row_vector=mlfw_column_vec_double_create_new_filled(10,5,NULL);
	if(row_vector==NULL)
	{
		printf("unable to create row vector\n");
		return 0;
	}
	copy_vector=mlfw_column_vec_double_create_new(5);
	if(copy_vector==NULL)
	{
		printf("unable to create copy vector\n");
		return 0;
	}
	mlfw_column_vec_double_copy(row_vector,copy_vector,2,4,1);
//	mlfw_column_vec_double_copy(row_vector,copy_vector,6,2,1);
//	mlfw_column_vec_double_copy(row_vector,copy_vector,2,6,1);
	print_column_vector(copy_vector);

	mlfw_column_vec_double_destroy(row_vector);
	mlfw_column_vec_double_destroy(copy_vector);

    return 0;
}

