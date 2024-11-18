//Generating random number, Every second, We have to provide a seed value to generate random number based on every second
//Using  srand() + rand() function
//We are apply system time based argument passes to srand for generating random number, Which would change every second

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
int x;
int i;
srand(time(NULL));		//Refer: eg3.c
for(i=0;i<5;i++)
{
x=rand();
printf("Generating %d random number: %d\n",i+1,x);
}

return 0;
}

