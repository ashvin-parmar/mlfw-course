//Learning generating random number between a range

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
int x,r,n;
int start=31;
int end=34;
srand(time(NULL));		//To be called only once
n=1;
for(x=start;x<=end;x++)
{
r=rand();
r=r%(end-start+1);
r+=start;
printf("%d generated number is %d\n",n++,r);
}
return 0;
}
