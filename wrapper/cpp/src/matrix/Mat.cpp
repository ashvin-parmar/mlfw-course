#include <iostream>
extern "C" 
{
#include <mlfw_matrix.h>
}
#include<mlfwmatrix>
#include <mlfwexception>
using namespace std;
using namespace mlfw;

Mat::Mat(int row,int column) noexcept(false)
{
this->matrix=mlfw_mat_double_create_new((dimension_t)row,(dimension_t)column);
if(this->matrix==NULL) throw MLFWException("Memory issue");
}
Mat::Mat(int row,int column,double value) noexcept(false)
{
this->matrix=mlfw_mat_double_create_new_filled((dimension_t)row,(dimension_t)column,value,NULL);
if(this->matrix==NULL) throw MLFWException("Memory issue");
}

Mat::Mat(const Mat *other) noexcept(false)
{
printf("Here, copy constructor called");
if(this->matrix!=NULL) mlfw_mat_double_destroy(this->matrix);
this->matrix=NULL;
dimension_t rows,columns;
mlfw_mat_double_get_dimension(this->matrix,&rows,&columns);
this->matrix=mlfw_mat_double_create_new(rows,columns);
mlfw_mat_double_copy(this->matrix,other->matrix,0,0,0,0,rows-1,columns-1);
}

double Mat::get(int row,int column) noexcept(false)
{
return mlfw_mat_double_get(this->matrix,row,column);
}
void Mat::set(int row,int column,double value) noexcept(false)
{
mlfw_mat_double_set(this->matrix,row,column,value);
}
Mat::~Mat() noexcept(false)
{
mlfw_mat_double_destroy(this->matrix);
}


