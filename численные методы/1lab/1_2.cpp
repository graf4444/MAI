#include <iostream>
#include <vector>

using namespace std;

class TMatrix
{
private:
    double ** A;
    int n,m;

public:

    TMatrix() { this->n = this->m = 0; };

    TMatrix(int n){
        this->n = n;
        this->m = n;

        this->A = new double*[n];
        for (int i = 0; i < n; i++) {
            A[i] = new double[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(i == j) {
                    A[i][j] = 1;
                }
                else {
                    A[i][j] = 0;
                }
            }
        }
/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
*/        
    };
 
    TMatrix(int n, int m){
        this->n = n;
        this->m = m;

        this->A = new double*[n];
        for (int i = 0; i < n; i++) {
            A[i] = new double[m];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if(i == j) {
                    A[i][j] = 1;
                }
                else {
                    A[i][j] = 0;
                }
            }
        }

/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
*/        
    };
        
    double* operator [] (int const x) { return A[x]; };

    void operator = (TMatrix sec) {
        if(this->n == 0 || this->m == 0) {
            this->A = new double*[sec.sizeRow()];
            for (int i = 0; i < sec.sizeCol(); i++) {
                this->A[i] = new double[sec.sizeCol()];
            }
        }
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                this->A[i][j] = sec[i][j];
            }
        }
    };


    void read() {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                cin >> A[i][j];
            }
        }
    }

    void print() {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j <= this->m; j++) {
                if (i == 0 && j == 0)
                    cout << "/ ";
                if (i == 0 && j == this->m)
                    cout << "\\ ";
                if (i == this->n-1 && j == 0)
                    cout << "\\ ";
                if (i == this->n-1 && j == this->m)
                    cout << "/ ";
                if ((j == 0 && i >= 1 && i < this->n-1) || (j == this->m && i >= 1 && i < this->n-1))
                    cout << "| ";
                if (i < this->n && j < this->m)
                    cout << A[i][j] << " ";
            }
            cout << endl;
        }
    };

    int sizeRow() { return this->n; };
    int sizeCol() { return this->m; };

    void swapRow(int k, int l) {
        for (int i = 0; i < this->n; i++) {
            double tmp = this->A[k][i];
            A[k][i] = A[l][i];
            A[l][i] = tmp;
        }
    };

    void swapCol(int k, int l) {
         for (int i = 0; i < this->m; i++) {
            double tmp = this->A[i][k];
            A[i][k] = A[i][l];
            A[i][l] = tmp;
        }
    };
};

void Solve(TMatrix& iM, vector <double>& iR)
{
    
    vector <double> P; 
    vector <double> Q; 

    int ja = 0;
    int jb = 1;
    int jc = 1;

    P.push_back( ((-1)*iM[0][jc++]) / iM[0][0] );
    Q.push_back( iR[0] / iM[0][0] );


    for (int i = 1; i < iM.sizeRow(); i++) {
        P.push_back( ((-1)*iM[i][jc]) / (iM[i][jb] + iM[i][ja] * P[i-1]) );
        Q.push_back( (iR[i] - iM[i][ja]*Q[i-1]) / (iM[i][jb] + iM[i][ja] * P[i-1]) );
        ++ja;
        ++jb;
        ++jc;
    }
/*
    for (int i = 0; i < P.size(); i++)
        cout << P[i] << " ";
    cout << endl;
    for (int i = 0; i < Q.size(); i++)
        cout << Q[i] << " ";
    cout << endl;
*/
    vector <double> res(iM.sizeRow()+1, 0);
    for (int i = iM.sizeRow()-1; i >= 0; i--) {
        res[i] = P[i]*res[i+1] + Q[i];
    }

    for (int i = 0; i < iM.sizeRow(); i++) {
        cout << "x_" << i << " = " << res[i] << endl;
    }

}

int main()
{
   int n;
    cin >> n;
    TMatrix A(n);
    vector <double> resA;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n+1; j++) {
            double tmp;
            cin >> tmp;
            if (j < n)
                A[i][j] = tmp;
            else
                resA.push_back(tmp);
        }
    }

    A.print();
    for (int i = 0; i < resA.size(); i++) {
        cout << resA[i] << endl;
    }
    cout << endl;

    Solve(A,resA);
    return 0;
}
