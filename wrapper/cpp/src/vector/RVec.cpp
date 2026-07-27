#include <iostream>
extern "C" 
{
#include <mlfw_vector.h>
}
#include<mlfwvector>
#include <mlfwexception>

using namespace std;
using namespace mlfw;

RVec::RVec()
{
this->vec=NULL;
this->_size=0;
}
RVec::RVec(dimension_t size) noexcept(false)
{
if(size<=0) throw MLFWException("size cannot be zero or negative.");
this->vec=mlfw_row_vec_double_create_new(size);
if(this->vec==NULL) throw MLFWException("memory issue");
this->_size=size;
}
RVec::RVec(dimension_t size,double value) noexcept(false)
{
if(size<=0) throw MLFWException("size cannot be zero or negative");
this->vec=mlfw_row_vec_double_create_new_filled(size,value,NULL);
if(this->vec==NULL) throw MLFWException("memory issue");
this->_size=size;
}
RVec::RVec(const RVec &other) noexcept(false)
{
dimension_t size;
size=other._size;
this->vec=mlfw_row_vec_double_create_new(size);
if(this->vec==NULL) throw MLFWException("memory issue");
mlfw_row_vec_double_copy(this->vec,other.vec,0,0,size-1);
this->_size=size;
}
RVec& RVec::operator=(const RVec &other) noexcept(false)
{
dimension_t size;
if(this->vec!=NULL) mlfw_row_vec_double_destroy(this->vec);
this->vec=NULL;
this->_size=0;
size=other._size;
this->vec=mlfw_row_vec_double_create_new(size);
if(this->vec==NULL) throw MLFWException("memory issue");
mlfw_row_vec_double_copy(this->vec,other.vec,0,0,size-1);
this->_size=size;
return *this;
}

RVec::~RVec() noexcept(false)
{
if(this->vec!=NULL) mlfw_row_vec_double_destroy(this->vec);
}

double RVec::get(dimension_t index) noexcept(false)
{
if(this->vec==NULL || index<0 || index>=this->_size) throw MLFWException("index out of bounds.");
return mlfw_row_vec_double_get(this->vec,index);
}
void RVec::set(dimension_t index,double value) noexcept(false)
{
if(this->vec==NULL || index<0 || index>=this->_size) throw MLFWException("index out of bounds.");
mlfw_row_vec_double_set(this->vec,index,value);
}

RVec* RVec::from(string file_name,int file_format,std::vector<string> &header) noexcept(false)
{
mlfw_row_vec_double *vector=NULL;
mlfw_row_vec_string *row_header=NULL;
dimension_t header_size;
dimension_t size;
char *value;
string val;
RVec *rvec;
if(file_name.size()<=0) throw MLFWException("file name required");

if(file_format==Vector::CSV)
{
vector=mlfw_row_vec_double_from_csv(file_name.c_str(),NULL,&row_header);
}
else
{
throw MLFWException("Invalid file format, Must from [CSV]");
}
if(vector==NULL || row_header==NULL)
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
mlfw_row_vec_string_destroy(row_header);
size=mlfw_row_vec_double_get_size(vector);
rvec=new RVec();
rvec->vec=vector;
rvec->_size=size;
return rvec;
}
void RVec::to(RVec *row_vector,string file_name,int file_format,std::vector<string> &header) noexcept(false)
{
mlfw_row_vec_double *vec=NULL;
mlfw_row_vec_string *row_header=NULL;
dimension_t header_size;
dimension_t size;
index_t i; 
if(file_name.size()<=0) throw MLFWException("file name required");
if(row_vector==NULL) throw MLFWException("row vector required");
vec=row_vector->vec;
if(vec==NULL || row_vector->_size==0) throw MLFWException("row vector required");
if(header.size()<row_vector->_size) throw MLFWException("complete header required");
row_header=mlfw_row_vec_string_create_new(row_vector->_size);
for(i=0;i<row_vector->_size;i++)
{
	mlfw_row_vec_string_set(row_header,i,header[i].c_str());
}
if(file_format==Vector::CSV)
{
mlfw_row_vec_double_to_csv(vec,file_name.c_str(),row_header);
}
else
{
throw MLFWException("Invalid file format, Must from [CSV]");
}
mlfw_row_vec_string_destroy(row_header);
}
void RVec::to(string file_name,int file_format,std::vector<string> &header) noexcept(false)
{
mlfw_row_vec_string *row_header=NULL;
dimension_t header_size;
index_t i; 
if(file_name.size()<=0) throw MLFWException("file name required");
if(this->vec==NULL || this->_size==0) throw MLFWException("row vector required");
if(header.size()<this->_size) throw MLFWException("complete header required");
row_header=mlfw_row_vec_string_create_new(this->_size);
for(i=0;i<this->_size;i++)
{
	mlfw_row_vec_string_set(row_header,i,header[i].c_str());
}
if(file_format==Vector::CSV)
{
mlfw_row_vec_double_to_csv(this->vec,file_name.c_str(),row_header);
}
else
{
throw MLFWException("Invalid file format, Must from [CSV]");
}
mlfw_row_vec_string_destroy(row_header);
}

dimension_t RVec::size() noexcept(false)
{
return this->_size;
}
Vector* RVec::transpose() noexcept(false)
{
return NULL;
}
Vector* RVec::fill(double value) noexcept(false)
{
return NULL;
}
double RVec::mean()	 noexcept(false)
{
return 0.0;
}

void fill(index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value) noexcept(false)
{

}

/*
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
*/
void RVec::copy(RVec *target,RVec *source,index_t target_start_index,index_t source_start_index,index_t source_end_index) noexcept(false)
{
if(target==NULL || target->vec==NULL) throw MLFWException("target required");
if(source==NULL || source->vec==NULL) throw MLFWException("source required");

dimension_t target_size;
dimension_t source_size;
bool valid=true;
target_size=target->_size;
source_size=source->_size;

if(target_start_index<0 || target_start_index>=target_size) valid=false;
if(!valid) throw MLFWException("invalid target index order passed");

if(source_start_index<0 || source_start_index>=source_size) valid=false;
if(source_end_index<0 || source_end_index>=source_size) valid=false;
if(source_start_index>source_end_index) valid=false;

if(target_start_index+(source_end_index-source_start_index)>=target_size) valid=false;
if(!valid) throw MLFWException("invalid source index order passed");

mlfw_row_vec_double_copy(target->vec,source->vec,target_start_index,source_start_index,source_end_index);
}
/*
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
*/

