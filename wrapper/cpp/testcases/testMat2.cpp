#include <iostream>
#include <mlfwmatrix>
#include <vector>
using namespace std;
using namespace mlfw;


int main(int argc, char *argv[]) 
{
vector<string> header;
string str="IceCreamSales.csv";
Mat *mat=Mat::from(str,Mat::CSV,header);
//printf("here");

vector<dimension_t> dimensions=mat->dimensions();
printf("Row: %d, Columns: %d\n",dimensions[0],dimensions[1]);

for(int i=0;i<header.size();i++)
{
printf("%s\n",header[i].c_str());
}
mat->to("something.csv",Mat::CSV,header);
printf("Rows: %d\n",mat->rows());
printf("Column: %d\n",mat->columns());

delete mat;
return 0;
}
