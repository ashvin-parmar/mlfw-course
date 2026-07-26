//generating random double type of numbers in a range, 
//generalised way provided by someone

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/**
 * Author: Ashvin
 * Date: 2026-07-26
 * Description: 
 */
int main() 
{
	int x;
	double value;
	double min,max;
	srand(time(NULL));
	min=-100.0;
	max=100.0;
	x=1;
	while(x<=10)
	{
	value=rand();
	value=((value*(max-min))/RAND_MAX)+min;
	printf("%lf\n",value);
	x++;
	}
	
    return 0;
}

