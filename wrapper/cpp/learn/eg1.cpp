#include <iostream>
#include <vector>
using namespace std;
class PQR
{
	private:
vector<vector<string>> data;
	public:
PQR()
{
	data.push_back(vector<string>({"nitin","suresh","ramesh"}));
	data.push_back(vector<string>({"someting","nothing","whatever"}));
}
	// Proxy class to handle the second [] operator
	class RowProxy {
		vector<string>& row;
	public:
		RowProxy(vector<string>& r) : row(r) {}
		
		// The second [] accesses the specific column
		string& operator[](int j) {
			return row[j];
		}
	};

	// The first [] returns the Proxy object
	RowProxy operator[](int i)
	{
		return RowProxy(data[i]);
	}
};

int main(int argc, char *argv[]) 
{
PQR pqr;
for(int i=0;i<2;i++)
{
for(int j=0;j<=2;j++)
{
	cout<<pqr[i][j];
}
cout<<endl;
}

string str=pqr[0][0];
cout<<"str data: "<<str<<endl;

pqr[0][0]="changed data";
str=pqr[0][0];
cout<<"str data: "<<str<<endl;
return 0;
}
