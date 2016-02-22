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

void SolveLU(TMatrix& iM, vector <double> iR) {
    TMatrix A(iM.sizeRow(), iM.sizeCol());
    TMatrix B(iM.sizeRow());
    TMatrix C(iM.sizeRow());

    A = iM;
    int permutation = 0;

    for (int i = 0; i < A.sizeRow()-1; i++) {
        double cur = A[i][i];
        if (cur == 0) {
            for (int q = i+1; q < A.sizeRow(); q++) {
                if(A[q][i] != 0) {
                    A.swapRow(i, q);
                    B.swapRow(i, q);
                    double tmp = iR[i];
                    iR[i] = iR[q];
                    iR[q] = tmp;
                    cur = A[q][i];
                    ++permutation;
                }
            }
        }
        for (int j = i+1; j < A.sizeCol(); j++) {
            double tmp = A[j][i] / cur;
            for (int k = i; k < A.sizeCol(); k++) {
                A[j][k] -= A[i][k] * tmp;
                B[j][k] += B[i][k] * tmp;
                C[j][k] -= B[i][k] * tmp;
            }
            iR[j] -= iR[i] * tmp;
        }
    }

    double det=1;

    for (int i = 0; i < A.sizeRow(); i++) {
        det *= A[i][i];
    }

    if (permutation%2 == 1)
        det *= -1;

    cout << endl;
    cout << "det = " << det << endl;

    cout << endl;
    cout << "L: " << endl;
    B.print();
    cout << endl;
    cout << "U: " << endl;
    A.print();
    cout << endl;

    if (det != 0) {
        vector <double> res(A.sizeRow(), 0);
        for (int i = A.sizeRow()-1; i >= 0; i--) {
            double tmp = iR[i];
            for (int j = A.sizeCol(); j >= i; j--) {
                tmp += (-1)*A[i][j]*res[j];
            }
            res[i] = tmp/A[i][i];
        }
        for (int i = 0; i < A.sizeRow(); i++) {
            cout << "x_" << i << " = " << res[i] << endl;
        }


        TMatrix A1(A.sizeRow());

        for (int i = 0; i < A1.sizeRow(); i++) {
            for (int j = 0; j < A1.sizeCol(); j++) {
                A1[i][j] = 0;
            }
        }
/*
        cout << endl;
        C.print();
        cout << endl;
*/        
        for (int k = 0; k < A.sizeRow(); k++) {
		    vector <double> tmpV(A.sizeRow(), 0);
		    vector <double> tmpRes(A.sizeRow(), 0);

            for (int i = 0; i < A.sizeRow(); i++) {
                tmpV[i] = C[i][k];
            }
		    for (int i = A.sizeRow()-1; i >= 0; i--) {
		        double tmp = tmpV[i];
		        for (int j = A.sizeCol(); j >= i; j--) {
		            tmp += (-1)*A[i][j]*tmpRes[j];
		        }
		        tmpRes[i] = tmp/A[i][i];
		    }
		    for (int i = 0; i < A.sizeRow(); i++) {
		    	A1[i][k] = tmpRes[i];
		    }
        }
        
		cout << endl << "A^{-1}:" << endl;
        A1.print();
        cout << endl;
/*
        for (int i = A.sizeRow()-1; i >=0; i--) {
            for (int k = 0; k < C.sizeCol(); k++) {
                double tmp = C[i][k];
//                cout << C[i][k] << " ";
                for (int j = A.sizeCol()-1; j > i; j--) {
                    if (i == A.sizeRow()-1) {
                        tmp += (-1)*A[i][k]*A1[i][k];
//                        cout << A[i][j] << " " << A1[i][k] << endl;
                    }
                    else {
                        tmp += (-1)*A[i][j]*A1[i+1][k];
//                        cout << A[i][j] << " " << A1[i+1][k] << endl;
                    }
                }
//                cout << "A1[" << i << "]" << "[" << k << "] = " << tmp << " / " << A[i][i] << " = " << tmp/A[i][i] << " " << endl;
                A1[i][k] = tmp/A[i][i];
 //               A1.print();
            }
//            cout << endl;
        }

        cout << endl << "A^{-1}:" << endl;
        A1.print();
        cout << endl;
*/
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
//    A.read();
//    A.print();

//    A.swapCol(0,2);
//    A.print();
//    A.swapRow(0,2);
//    A.print();

    SolveLU(A, resA);

    return 0;
}
