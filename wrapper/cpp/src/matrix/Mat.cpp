#include <iostream>
extern "C" 
{
#include <mlfw_matrix.h>
}
#include<mlfwmatrix>
#include <mlfwexception>
using namespace std;
using namespace mlfw;

Mat::Mat()
{
this->matrix=NULL;
this->r=0;
this->c=0;
}
Mat::Mat(dimension_t rows,dimension_t columns) noexcept(false)
{
if(rows==0 || columns==0) throw MLFWException("row or column should not be zero.");
this->matrix=mlfw_mat_double_create_new(rows,columns);
if(this->matrix==NULL) throw MLFWException("memory issue");
this->r=rows;
this->c=columns;
}
Mat::Mat(dimension_t rows,dimension_t columns,double value) noexcept(false)
{
if(rows==0 || columns==0) throw MLFWException("row or column should not be zero.");
this->matrix=mlfw_mat_double_create_new_filled(rows,columns,value,NULL);
if(this->matrix==NULL) throw MLFWException("memory issue");
this->r=rows;
this->c=columns;
}

Mat::Mat(const Mat &other) noexcept(false)
{
printf("Here, copy constructor called");

dimension_t rows,columns;
rows=other.r;
columns=other.c;
this->matrix=mlfw_mat_double_create_new(rows,columns);
mlfw_mat_double_copy(other.matrix,this->matrix,0,0,0,0,rows-1,columns-1);
if(this->matrix==NULL) throw MLFWException("memory issue");
this->r=rows;
this->c=columns;
}
Mat& Mat::operator=(const Mat &other) noexcept(false)
{
if(this->matrix!=NULL) mlfw_mat_double_destroy(this->matrix);
this->matrix=NULL;
this->r=0;
this->c=0;

dimension_t rows,columns;
rows=other.r;
columns=other.c;
this->matrix=mlfw_mat_double_create_new(rows,columns);
mlfw_mat_double_copy(other.matrix,this->matrix,0,0,0,0,rows-1,columns-1);
if(this->matrix==NULL) throw MLFWException("memory issue");
this->r=rows;
this->c=columns;
return *this;
}

double Mat::get(index_t row,index_t column) noexcept(false)
{
return mlfw_mat_double_get(this->matrix,row,column);
}
void Mat::set(index_t row,index_t column,double value) noexcept(false)
{
mlfw_mat_double_set(this->matrix,row,column,value);
}
Mat::~Mat() noexcept(false)
{
mlfw_mat_double_destroy(this->matrix);
}
Mat * Mat::from(string file_name,int file_format,vector<string> &header)
{
if(file_name.size()==0) throw MLFWException("file name required");

mlfw_mat_double *matrix=NULL;
mlfw_row_vec_string *row_header=NULL;
dimension_t header_size;
dimension_t rows,columns;
char * value=NULL;
string val;
Mat *mat;
if(file_format==Matrix::CSV)
{
matrix=mlfw_mat_double_from_csv(file_name.c_str(),NULL,&row_header);
}
else
{
throw MLFWException("Invalid file format, Must from [CSV]");
}
if(matrix==NULL || row_header==NULL)
{
throw MLFWException("memory issue");
}
header_size=mlfw_row_vec_string_get_size(row_header);
for(index_t i=0;i<header_size;i++)
{
mlfw_row_vec_string_get(row_header,i,&value);
if(value!=NULL) header.push_back(value);
else header.push_back("");
free(value);
value=NULL;
}
mlfw_mat_double_get_dimension(matrix,&rows,&columns);
mat=new Mat();
mat->matrix=matrix;
mat->r=rows;
mat->c=columns;
return mat;
}
void Mat::to(Mat *matrix,string file_name,int file_format,vector<string> &header)
{
if(file_name.size()==0) throw MLFWException("file name required");
if(matrix==NULL || matrix->matrix) throw MLFWException("empty matrix provided to store in file");
mlfw_row_vec_string *row_header=mlfw_row_vec_string_create_new((dimension_t)header.size());
if(row_header==NULL) throw MLFWException("memory issue");
for(index_t i=0;i<header.size();i++)
{
mlfw_row_vec_string_set(row_header,i,header[i].c_str());
}
if(file_format==Matrix::CSV)
{
mlfw_mat_double_to_csv(matrix->matrix,file_name.c_str(),row_header);
}
else
{
throw MLFWException("Invalid file format, Must from [CSV]");
}
}
void Mat::to(string file_name,int file_format,vector<string> &header)
{
if(file_name.size()==0) throw MLFWException("file name required");
if(this->matrix==NULL) throw MLFWException("empty matrix provided to store in file");
mlfw_row_vec_string *row_header=mlfw_row_vec_string_create_new((dimension_t)header.size());
if(row_header==NULL) throw MLFWException("memory issue");
for(index_t i=0;i<header.size();i++)
{
mlfw_row_vec_string_set(row_header,i,header[i].c_str());
}
if(file_format==Matrix::CSV)
{
mlfw_mat_double_to_csv(this->matrix,file_name.c_str(),row_header);
}
else
{
throw MLFWException("Invalid file format, Pick from [CSV]");
}
}
dimension_t Mat::rows()
{
return this->r;
}
dimension_t Mat::columns()
{
return this->c;
}
vector<dimension_t> Mat::dimensions()
{
	return {this->r,this->c};
}

void Mat::shuffle(unsigned int shuffle_times)
{
if(shuffle_times==0) return;
mlfw_mat_double *shuffle_matrix=NULL;
shuffle_matrix=mlfw_mat_double_shuffle(this->matrix,shuffle_times,NULL);
if(shuffle_matrix==NULL)
{
throw MLFWException("Unable to shuffle matrix");
}
mlfw_mat_double_destroy(this->matrix);
this->matrix=shuffle_matrix;
}
Mat* Mat::get_shuffle(unsigned int shuffle_times)
{
if(shuffle_times==0) return new Mat(*this);
mlfw_mat_double *shuffle_matrix=NULL;
shuffle_matrix=mlfw_mat_double_shuffle(this->matrix,shuffle_times,NULL);
if(shuffle_matrix==NULL)
{
throw MLFWException("Unable to shuffle matrix");
}
Mat *mat=new Mat();
mat->matrix=shuffle_matrix;
mat->r=this->r;
mat->c=this->c;
return mat;
}

Mat* Mat::transpose()
{
mlfw_mat_double *transpose_matrix=NULL;
transpose_matrix=mlfw_mat_double_transpose(this->matrix,NULL);
if(transpose_matrix==NULL)
{
throw MLFWException("unable to transpose matrix");
}
Mat *mat=new Mat();
mat->matrix=transpose_matrix;
mat->r=this->c;
mat->c=this->r;
return mat;
}
double Mat::minimum(index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
return mlfw_mat_double_get_minimum(this->matrix,start_row_index,end_row_index,start_column_index,end_column_index);
}
double Mat::maximum(index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
return mlfw_mat_double_get_maximum(this->matrix,start_row_index,end_row_index,start_column_index,end_column_index);
}
double Mat::mean(index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
return mlfw_mat_double_get_mean(this->matrix,start_row_index,end_row_index,start_column_index,end_column_index);
}
double Mat::standard_deviation(index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
return mlfw_mat_double_get_standard_deviation(this->matrix,start_row_index,end_row_index,start_column_index,end_column_index);
}
void Mat::resize(dimension_t new_rows_count,dimension_t new_columns_count)
{
if(new_rows_count<=0 || new_columns_count<=0)
{
throw MLFWException("new rows and columns count can not lesser than equal to zero");
}
mlfw_mat_double_reshape(&this->matrix,new_rows_count,new_columns_count);
if(this->matrix==NULL) throw MLFWException("memory issue");
}

void Mat::operator<<(dimension_t how_many_places_to_shift)
{
	if(how_many_places_to_shift<=0) return; 
	mlfw_mat_double_right_shift(this->matrix,how_many_places_to_shift);
}
void Mat::operator>>(dimension_t how_many_places_to_shift)
{
		if(how_many_places_to_shift<=0) return; 
	mlfw_mat_double_left_shift(this->matrix,how_many_places_to_shift);
}
//double operator[][](dimension_t row,dimension_t column) noexcept(false);
//void operator[][]=(dimension_t row,dimension_t column,double value) noexcept(false);

void Mat::copy(Mat *target,Mat *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index)
{
if(target==NULL || target->matrix || source==NULL || source->matrix==NULL) throw MLFWException("target or source required");

dimension_t target_rows=target->r;
dimension_t target_columns=target->c;
dimension_t source_rows=source->r;
dimension_t source_columns=source->c;
bool valid=true;
if(from_target_row_index<0 || from_target_row_index>=target_rows) valid=false;
if(from_target_column_index<0 || from_target_column_index>=target_columns) valid=false;

if(from_source_row_index<0 || from_source_row_index>=source_rows) valid=false;
if(from_source_column_index<0 || from_source_column_index>=source_columns) valid=false;   
if(to_source_row_index<0 || to_source_row_index>=source_rows) valid=false;
if(to_source_column_index<0 || to_source_column_index>=source_columns) valid=false;   
if(from_source_row_index>to_source_row_index) valid=false;
if(from_source_column_index>to_source_column_index) valid=false;
if(!valid) throw MLFWException("invalid row/column index order passed");

mlfw_mat_double_copy(target->matrix,source->matrix,from_target_row_index,from_target_column_index,from_source_row_index,from_source_column_index,to_source_row_index,to_source_column_index);
}
void Mat::fill(index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value)
{
bool valid=true;
dimension_t matrix_rows=this->r;
dimension_t matrix_columns=this->c;

if(from_row_index<0 || from_row_index>=matrix_rows) valid=false;
if(from_column_index<0 || from_column_index>=matrix_columns) valid=false;
if(to_row_index<0 || to_row_index>=matrix_rows) valid=false;
if(to_column_index<0 || to_column_index>=matrix_columns) valid=false;
if(from_row_index>to_row_index) valid=false;
if(from_column_index>to_column_index) valid=false;
if(!valid) throw MLFWException("invalid row/column index order passed");

mlfw_mat_double_fill(this->matrix,from_row_index,from_column_index,to_row_index,to_column_index,value);
}


