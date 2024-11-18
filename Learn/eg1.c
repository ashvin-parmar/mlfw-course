//Generating random number, But there are same type of number generated every time of execution
//Only rand() function

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
int x;
int i;
for(i=0;i<5;i++)
{
x=rand();
printf("Generating %d random number: %d\n",i+1,x);
}

return 0;
}

