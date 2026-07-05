#include <iostream>
#include <vector>
#include <string>
using namespace std;

// A matrix-like class holding large string data.
// RowProxy stores only the row index + parent reference,
// NOT a copy of the data (data can be arbitrarily large).
class Matrix
{
private:
    vector<vector<string>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<string>(c, ""))
    {
    }

    // -------------------------------------------------------
    // Proxy: saves only index 'i' and a reference to Matrix.
    // NO data copy at all.
    // -------------------------------------------------------
    class RowProxy
    {
        Matrix& mat;   // Reference to parent (no data copy)
        int     row;   // Saved 'i' index

    public:
        RowProxy(Matrix& m, int i) : mat(m), row(i) {}

        // --- Getter: pqr[i][j] ---
        const string& operator[](int j) const
        {
            if (j < 0 || j >= mat.cols)
                throw out_of_range("Column index out of range");
            return mat.data[row][j];
        }

        // --- Setter: pqr[i][j] = value ---
        string& operator[](int j)
        {
            if (j < 0 || j >= mat.cols)
                throw out_of_range("Column index out of range");
            return mat.data[row][j];
        }
    };

    // Const version of RowProxy for read-only access
    class ConstRowProxy
    {
        const Matrix& mat;
        int           row;

    public:
        ConstRowProxy(const Matrix& m, int i) : mat(m), row(i) {}

        const string& operator[](int j) const
        {
            if (j < 0 || j >= mat.cols)
                throw out_of_range("Column index out of range");
            return mat.data[row][j];
        }
    };

    // --- First []: returns RowProxy saving only 'i' ---
    RowProxy operator[](int i)
    {
        if (i < 0 || i >= rows)
            throw out_of_range("Row index out of range");
        return RowProxy(*this, i);      // Only 'i' + &parent stored
    }

    // Const overload for read-only contexts
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

    // --- Setter: mat[i][j] = value ---
    mat[0][0] = "Alice";    mat[0][1] = "Bob";    mat[0][2] = "Charlie";
    mat[1][0] = "Dave";     mat[1][1] = "Eve";    mat[1][2] = "Frank";
    mat[2][0] = "Grace";    mat[2][1] = "Heidi";  mat[2][2] = "Ivan";

    mat.print();

    // --- Getter: read via mat[i][j] ---
    cout << "\nGetter: mat[1][2] = " << mat[1][2] << endl;

    // --- Setter: update a value ---
    mat[1][2] = "UPDATED";
    cout << "After mat[1][2] = \"UPDATED\":" << endl;
    mat.print();

    // --- const Matrix (only getter available) ---
    const Matrix& cmat = mat;
    cout << "\nConst access: cmat[0][0] = " << cmat[0][0] << endl;

    // --- Bounds checking ---
    try {
        mat[5][0] = "out of bounds";
    } catch (const out_of_range& e) {
        cout << "\nCaught: " << e.what() << endl;
    }

    return 0;
}
