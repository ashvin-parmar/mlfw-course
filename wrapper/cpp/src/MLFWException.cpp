#include<mlfwexception>
using namespace mlfw;

MLFWException::MLFWException()
{
this->messege="";
}
MLFWException::MLFWException(const MLFWException &other)
{
this->messege=other.messege;
}
MLFWException::MLFWException(string messege)
{
this->messege=messege;
}
MLFWException& MLFWException::operator=(const MLFWException &other)
{
this->messege=other.messege;
return *this;
}
MLFWException::~MLFWException() throw()
{
// Do Nothing
}
const char * MLFWException::what() const throw()
{
return this->messege.c_str();
}

