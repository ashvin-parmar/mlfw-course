# Module-3

## Implementing Normal Equation
-- pending --

## Implementing Logistic Regression - binary classification
- Start from lecture number [C-12] Logistic Regression

### Lecture 12
- discussing why logistic regression gradient decent used, what is difference between logistic and linear regression.
- terminology used in industry to introduce terms for in general around machine learning.
- use of sigmoid function as hypothesis function.
- use of Binary Cross Entropy (BCE) as a cost function, instead of using MSE, cost value (error value)has been found out based on (actual - predicted value over sigmoid function).
- update parameter: based on the cost, new parameters are generated, which has been used to process for next iteration.

### Sigmoid function: **hypothesis function**
sigmoid(X0)=H0(X)
Sigmoid function formula: 1/(1+e^(-z))


### Binary Cross Entropy (BCE): **cost function**
formula - complex unable to write
BCE: Binary Cross Entropy formula demonstration

	Sigmoid value is from {0,1}
	if we provide 1 and checks for 0, then chances are infinite. not possible case.
	if we provide 1 and checks for 1, then chances are nan

	if we provide actual=1 then checks for near to 1 value between 0.000....001 to 0.999999.....99 closer to 1 chances
	if we provide actual=0 then checks for near to 0 value  between 0.000....001 to 0.99999.....99

**
BCE=(-1/m)*(sumission of { [left] + [right] })

	[left] =  -( (  Y(i)) * log[(  h0(X(i)))] )
	[right]=  -( (1-Y(i)) * log[(1-h0(X(i)))] )
**

### update parameters
similar to liner equation [copy-pasted and changed based on requirement]






