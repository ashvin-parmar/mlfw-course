//Approuch 2: Strassens algorithm: 7 equations to solve matrix multiplication, which is optimized required only 7 multiplication. Based on Master's theorem its complexity is O(n^2.8). Which is quite optimized. Not much optimized, but when things come to big datasets, its matters a lot. Its applied only on 2*2 Matrix.

#include <stdio.h>
#include <mlfw_matrix.h>
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
	
	double A,B,C,D,E,F,G,H;
	double e1,e2,e3,e4,e5,e6,e7;

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

	A=mlfw_mat_double_get(m1,0,0);
	B=mlfw_mat_double_get(m1,0,1);
	C=mlfw_mat_double_get(m1,1,0);
	D=mlfw_mat_double_get(m1,1,1);

	E=mlfw_mat_double_get(m2,0,0);
	F=mlfw_mat_double_get(m2,0,1);
	G=mlfw_mat_double_get(m2,1,0);
	H=mlfw_mat_double_get(m2,1,1);

	e1=A*(F-H);
	e2=(A+B)*H;
	e3=(C+D)*E;
	e4=D*(G-E);
	e5=(A+D)*(E+H);
	e6=(B-D)*(G+H);
	e7=(A-C)*(E+F);

	m3=mlfw_mat_double_create_new(rows,columns);
	mlfw_mat_double_set(m3,0,0,e5+e4-e2+e6);
	mlfw_mat_double_set(m3,0,1,e1+e2);
	mlfw_mat_double_set(m3,1,0,e3+e4);
	mlfw_mat_double_set(m3,1,1,e1+e5-e3-e7);


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

