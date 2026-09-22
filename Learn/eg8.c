#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
BCE: Binary Cross Entropy formula demonstration

	Sigmoid value is from {0,1}
	if we provide 1 and checks for 0, then chances are infinite. not possible case.
	if we provide 1 and checks for 1, then chances are nan

	if we provide actual=1 then checks for near to 1 value between 0.000....001 to 0.999999.....99 closer to 1 chances
	if we provide actual=0 then checks for near to 0 value  between 0.000....001 to 0.99999.....99

Sigmoid function formula: 1/(1+e^(-z))
BCE=(-1/m)*(sumission of { [left] + [right] })
	
	[left] =  -( (  Y(i)) * log[(  h0(X(i)))] )
	[right]=  -( (1-Y(i)) * log[(1-h0(X(i)))] )

*/


int main(int argc,char *argv[])
{
	char *end;
	double actual;
	double predicted;
	double a,b,c;	// a left part of the cost function
					// b right part of the cost function
					// c - actual cost
	if(argc!=3)
	{
		printf("Pass actual and predicted values\n");
		return 0;
	}

	actual=strtod(argv[1],&end);
	predicted=strtod(argv[2],&end);
	a=-actual*log(predicted);
	b=-(1-actual)*log(1-predicted);
	c=a+b;
	printf("Cost is: %lf\n",c);
    return 0;
}

