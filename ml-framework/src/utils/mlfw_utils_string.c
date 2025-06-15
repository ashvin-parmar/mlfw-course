#include<mlfw_utils.h>
#include<stdio.h>
int strcmp_case_insensitive(const char *left,const char *right)
{
//This function should return 0 if both are same
//If the left operand is greater than the right one then return +ve
//else return -ve
char a,b;
if(left==NULL && right==NULL) return 0;
if(left==NULL) return -1;
if(right==NULL) return 1; 
while(*left!='\0' && *right!='\0')
{	
a=*left;
b=*right;
if(a>=97 &&  a<=122) a-=32;
if(b>=97 && b<=122) b-=32;
if(a!=b) return a-b;
left++;
right++;
}
return (*left)-(*right);
}
