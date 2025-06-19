#include<mlfw_utils.h>
#include<stdio.h>
int mlfw_strcmp_case_insensitive(const char *left,const char *right)
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
void mlfw_uint32_to_binary(uint32_t number,char *binary_string)
{
int i,j=0;
int bit;
for(i=31,j=0;i>=0;i--,j++)
{
bit=(number>>i) & 1;
if(bit==0) binary_string[j]='0';
else 	   binary_string[j]='1';
}
binary_string[j]='\0';
}
