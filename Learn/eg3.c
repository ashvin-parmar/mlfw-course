//Learning somehing about time() function

#include<stdio.h>
#include<time.h>
int main()
{
long int i;
i=time(NULL);
printf("%ld\n",i);		//Specifier to represent a long int value

return 0;
}
