#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Author: Ashvin
 * Date: 2026-07-30
 * Description: 
 */
int main(int argc,char *argv[]) {
	int num;
	int y;

	double val;
	double yy;
	char *x;
	num=atoi(argv[0]);
	val=strtod(argv[0],&x);

	printf("%d\n",num&(num-1));
	printf("%d\n",(16)&(15));
	printf("%d\n",(4)&(3));
	printf("%d\n",(31)&(30));
	printf("%d\n",(14)&(13));
	printf("%d\n",num&num);

	yy=log2(val);
	if(floor(yy)==ceil(yy)) printf("Yes, num is power of 2\n");
	else printf("No, num is not power of 2\n");
	
	y=num;
	while(y>2)
	{
		if(y%2==1) break;
		y/=2;
	}
	if(y>2) printf("No, num is not power of 2\n");
	else printf("Yes, num is power of 2\n");


    return 0;
}

