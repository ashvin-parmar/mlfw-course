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
        PQR& parent;
        int rowIndex; // Saves the 'i' index
    public:
        // Save the parent reference and the 'i' index
        RowProxy(PQR& p, int i) : parent(p), rowIndex(i) {}
        
        // The second [] accesses the specific column using saved rowIndex
        string& operator[](int j) {
            return parent.data[rowIndex][j]; // Access using 'i' and 'j'
        }
    };

    // The first [] returns the Proxy object saving the 'i' index
    RowProxy operator[](int i)
    {
        return RowProxy(*this, i);
    }
};

int main(int argc, char *argv[]) 
{
    PQR pqr;
    
    cout << "Original data:" << endl;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j <= 2; j++)
        {
            cout << pqr[i][j] << " ";
        }
        cout << endl;
    }

    string str = pqr[0][0];
    cout << "\nstr data: " << str << endl;

    pqr[0][0] = "changed data";
    str = pqr[0][0];
    cout << "str data after change: " << str << endl;

    return 0;
}
