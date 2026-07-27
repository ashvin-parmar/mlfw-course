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

for(int i=0;i<mat.rows();i++)
{
for(int j=0;j<mat.columns();j++)
{
printf("%d, ",mat.get(i,j));
}
printf("\n");
}
mat.shuffle(3);
for(int i=0;i<mat.rows();i++)
{
for(int j=0;j<mat.columns();j++)
{
printf("%d, ",mat.get(i,j));
}
printf("\n");
}

Mat *tmat=mat.transpose();
for(int i=0;i<mat.rows();i++)
{
for(int j=0;j<mat.columns();j++)
{
printf("%d, ",tmat.get(i,j));
}
printf("\n");
}

printf("Minium of first col: "+mat.minimum(0,this->rows-1));


delete mat;
return 0;
}
