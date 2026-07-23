#include <stdio.h>
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
/**
 * Author: Ashvin
 * Date: 2026-07-24
 * Description: 
 */
int main()
{
	mlfw_mat_double *matrix;
	mlfw_mat_double *copy_matrix;
	mlfw_row_vec_string *header;
	dimension_t rows,columns;
	index_t r,c;

	matrix=mlfw_mat_double_from_csv("mat_2x2_1.csv",NULL,&header);
	mlfw_mat_double_get_dimension(matrix,&rows,&columns);

	copy_matrix=mlfw_mat_double_create_copy(matrix,0,0,rows-1,columns-1,NULL);
	if(copy_matrix==NULL)
	{
		printf("Some problem creating copy matrix\n");
		mlfw_mat_double_destroy(matrix);
		return 0;
	}
	mlfw_mat_double_get_dimension(copy_matrix,&rows,&columns);
	for(r=0;r<rows;r++)
	{
		for(c=0;c<columns;c++)
		{
			printf("%lf ",mlfw_mat_double_get(copy_matrix,r,c));
		}
		printf("\n");
	}
	mlfw_mat_double_destroy(matrix);
	mlfw_mat_double_destroy(copy_matrix);
	
    return 0;
}

