#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Matrix
{
private:
    vector<vector<string>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<string>(c, "")) {}

    // -----------------------------------------------------------
    // ValueProxy: holds (i, j) + parent ref.
    // NEVER exposes string& to the outside world.
    // Controls ALL access via operator= (setter) and operator string (getter).
    // -----------------------------------------------------------
    class ValueProxy
    {
        Matrix& mat;
        int     row, col; // Both i and j saved here

    public:
        ValueProxy(Matrix& m, int i, int j) : mat(m), row(i), col(j) {}

        // --- Setter: mat[i][j] = "value" ---
        ValueProxy& operator=(const string& value)
        {
            mat.data[row][col] = value;  // Writes through controlled path only
            return *this;
        }

        // --- Getter: string s = mat[i][j] ---
        operator string() const
        {
            return mat.data[row][col];   // Returns a VALUE copy, never the address
        }

        // Allow cout << mat[i][j] directly
        friend ostream& operator<<(ostream& os, const ValueProxy& vp)
        {
            os << vp.mat.data[vp.row][vp.col];
            return os;
        }
    };

    // -----------------------------------------------------------
    // RowProxy: holds only 'i' + parent ref. No data copy.
    // operator[](j) returns ValueProxy — not string&.
    // -----------------------------------------------------------
    class RowProxy
    {
        Matrix& mat;
        int     row; // Saved 'i' index

    public:
        RowProxy(Matrix& m, int i) : mat(m), row(i) {}

        // Returns ValueProxy (NOT string&) — address never exposed
        ValueProxy operator[](int j)
        {
            if (j < 0 || j >= mat.cols)
                throw out_of_range("Column index out of range");
            return ValueProxy(mat, row, j); // Saves i and j
        }
    };

    // Const RowProxy for read-only matrix
    class ConstRowProxy
    {
        const Matrix& mat;
        int           row;

    public:
        ConstRowProxy(const Matrix& m, int i) : mat(m), row(i) {}

        string operator[](int j) const
        {
            if (j < 0 || j >= mat.cols)
                throw out_of_range("Column index out of range");
            return mat.data[row][j]; // Returns value copy only
        }
    };

    // --- First []: returns RowProxy with only 'i' saved ---
    RowProxy operator[](int i)
    {
        if (i < 0 || i >= rows)
            throw out_of_range("Row index out of range");
        return RowProxy(*this, i);
    }

    ConstRowProxy operator[](int i) const
    {
        if (i < 0 || i >= rows)
            throw out_of_range("Row index out of range");
        return ConstRowProxy(*this, i);
    }

    void print() const
    {
        cout << "Matrix [" << rows << "x" << cols << "]:" << endl;
        for (int i = 0; i < rows; i++)
        {
            cout << "  row[" << i << "]: ";
            for (int j = 0; j < cols; j++)
                cout << "[" << data[i][j] << "] ";
            cout << endl;
        }
    }
};

int main()
{
    Matrix mat(3, 3);

    // --- Setter: mat[i][j] = "value" via ValueProxy::operator= ---
    mat[0][0] = "Alice";   mat[0][1] = "Bob";    mat[0][2] = "Charlie";
    mat[1][0] = "Dave";    mat[1][1] = "Eve";    mat[1][2] = "Frank";
    mat[2][0] = "Grace";   mat[2][1] = "Heidi";  mat[2][2] = "Ivan";

    mat.print();

    // --- Getter: returns VALUE copy via ValueProxy::operator string ---
    string s = mat[1][2];
    cout << "\nGetter  mat[1][2] = " << s << endl;

    // --- cout directly via friend operator<< ---
    cout << "Direct  cout mat[0][0] = " << mat[0][0] << endl;

    // --- Update via setter ---
    mat[1][2] = "UPDATED";
    cout << "\nAfter mat[1][2] = \"UPDATED\":" << endl;
    mat.print();

    // --- Const matrix: only getter available, setter blocked at compile time ---
    const Matrix& cmat = mat;
    string cs = cmat[0][0];
    cout << "\nConst access cmat[0][0] = " << cs << endl;

    // --- Bounds check ---
    try {
        mat[5][0] = "bad";
    } catch (const out_of_range& e) {
        cout << "\nCaught: " << e.what() << endl;
    }

    return 0;
}
