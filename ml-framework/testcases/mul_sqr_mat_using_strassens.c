#include <stdio.h>
#include <mlfw_matrix.h>
#include <mlfw_operations.h>
#include <mlfw_vector.h>
/**
 * Author: Ashvin
 * Date: 2026-07-23
 * Description: 
 */
void print_matrix(mlfw_mat_double *matrix)
{
index_t r,c;
dimension_t rows,columns;
if(matrix==NULL) return;

mlfw_mat_double_get_dimension(matrix,&rows,&columns);
for(r=0;r<rows;++r)
{
	for(c=0;c<columns;++c)
	{
		printf("%10.2lf",mlfw_mat_double_get(matrix,r,c));
	}
	printf("\n");
}
}
int main(int argc,char *argv[]) 
{
	mlfw_mat_double *m1,*m2,*m3;
	mlfw_row_vec_string *h1,*h2;
	if(argc<3)
	{
		printf("usage: ./mul_sqr_mat.out <sqr_matrix_csv_file_name csv> <sql_matrix_2_csv_file_name>");
		return 0;
	}
	m1=mlfw_mat_double_from_csv(argv[1],NULL,&h1);
	if(m1==NULL)
	{
		printf("Unable to load csv: %s\n",argv[1]);
		return 0;
	}
	m2=mlfw_mat_double_from_csv(argv[2],NULL,&h2);
	if(m2==NULL)
	{
		printf("Unable to load csv: %s\n",argv[2]);
		mlfw_mat_double_destroy(m1);
		return 0;
	}

	m3=mlfw_strassens_multiply_double_matrix_with_matrix(m1,m2,NULL);
	if(m3==NULL)
	{
		mlfw_mat_double_destroy(m1);
	    mlfw_mat_double_destroy(m2);
		printf("Unable to multiply matrix, provide 2*2 matrix.\n");
		return 0;
	}
	printf("Multiplied matrix: \n");
	print_matrix(m3);

	mlfw_mat_double_destroy(m1);
    mlfw_mat_double_destroy(m2);
	mlfw_mat_double_destroy(m3);

    return 0;
}

