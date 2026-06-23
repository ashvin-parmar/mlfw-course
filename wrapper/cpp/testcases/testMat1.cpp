#include <iostream>
#include <mlfwmatrix>
using namespace std;
using namespace mlfw;
int main() 
{
Mat mat(2,2);
mat.set(0,0,1);
mat.set(0,1,10);
mat.set(1,0,2);
mat.set(1,1,20);

printf("%lf, %lf\n",mat.get(0,0),mat.get(0,1));
printf("%lf, %lf\n",mat.get(1,0),mat.get(1,1));


return 0;
}
