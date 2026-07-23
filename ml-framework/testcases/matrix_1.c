//Approuch 1: Multiply Matrix: using O(n^3) approuch with three loop to multiply matrix

#include <stdio.h>
#include <mlfw_matrix.h>
#include <mlfw_operations.h>
/**
 * Author: Ashvin
 * Date: 2026-07-23
 * Description: 
 */
int main() {
	int x[2][2]={{1,2},{3,4}};
	int y[2][2]={{10,20},{30,40}};
	index_t r,c;
	dimension_t rows,columns;
	mlfw_mat_double *m1,*m2,*m3;
	m1=mlfw_mat_double_create_new(2,2);
	m2=mlfw_mat_double_create_new(2,2);
	mlfw_mat_double_get_dimension(m1,&rows,&columns);
	for(r=0;r<rows;++r)
	{
		for(c=0;c<columns;++c)
		{
			mlfw_mat_double_set(m1,r,c,x[r][c]);
			mlfw_mat_double_set(m2,r,c,y[r][c]);
		}
	}

	m3=mlfw_multiply_double_matrix_with_matrix(m1,m2,NULL);

	printf("Result Matrix: \n");
	for(r=0;r<rows;++r)
	{
		for(c=0;c<columns;++c)
		{
			printf("%lf ",mlfw_mat_double_get(m3,r,c));
		}
		printf("\n");
	}

	mlfw_mat_double_destroy(m1);
	mlfw_mat_double_destroy(m2);
	mlfw_mat_double_destroy(m3);

    return 0;
}

