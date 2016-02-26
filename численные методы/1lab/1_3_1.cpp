#include <iostream>
#include <vector>

using namespace std;

double eps;

class TMatrix
{
private:
    double ** A;
    int n,m;

public:

    TMatrix() { this->n = this->m = 0; this->A = NULL; };

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
        
    double* operator [] (int const x) const { return A[x]; };

    TMatrix& operator = (TMatrix sec) {
        if(this->n != sec.sizeRow() || this->m != sec.sizeCol()) {
            if(A != NULL) {
                for (int i = 0; i < this->n; i++) {
                    delete[] this->A[i];
                }
                delete[] this->A;
                A = NULL;
            }

            this->A = new double*[sec.sizeRow()];
            for (int i = 0; i < sec.sizeRow(); i++) {
                this->A[i] = new double[sec.sizeCol()];
            }
            this->n = sec.sizeRow();
            this->m = sec.sizeCol();
            for (int i = 0; i < this->n; ++i) {
                for (int j = 0; j < this->m; ++j) {
                    this->A[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                this->A[i][j] = sec[i][j];
            }
        }
        return *this;
    };

    TMatrix operator * (const TMatrix& B) {
    	TMatrix product(this->n, B.sizeCol());
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < B.sizeCol(); j++) {
    			product[i][j] = 0;
    		}
    	}
		for (int row = 0; row < this->n; row++) {
		    for (int col = 0; col < B.sizeCol(); col++) {
		        for (int inner = 0; inner < this->m; inner++) {
		            product[row][col] += this->A[row][inner] * B[inner][col];
		        }
		    }
    	}
    	return product;
	};

    void read() {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                cin >> A[i][j];
            }
        }
    }

    void print() const {
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

    int sizeRow() const { return this->n; };
    int sizeCol() const { return this->m; };

    void swapRow(int k, int l) const {
        for (int i = 0; i < this->n; i++) {
            double tmp = this->A[k][i];
            A[k][i] = A[l][i];
            A[l][i] = tmp;
        }
    };

    void swapCol(int k, int l) const {
         for (int i = 0; i < this->m; i++) {
            double tmp = this->A[i][k];
            A[i][k] = A[i][l];
            A[i][l] = tmp;
        }
    };

    double norm() {
        double res = 0;
        double tmp = 0;
        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < this->n; j++) {
                if (A[j][i] < 0) {
                    tmp += (-1)*A[j][i];
                }
                else {
                    tmp += A[j][i];
                }
            }
            if (tmp > res) {
                res = tmp;
            }
            tmp = 0;
        }
        return res;
    };
};

void Solve(TMatrix& iM, vector<double> iR)
{
    for (int i = 0; i < iM.sizeRow(); i++) {
        if (iM[i][i] == 0) {
            for (int j = 0; j < iM.sizeRow(); j++) {
                if (iM[i][j] != 0)
                    iM.swapRow(i, j);
                    double tmp = iR[i];
                    iR[i] = iR[j];
                    iR[j] = tmp;
            }
        }
    }

    TMatrix beta(iR.size(), 1);
    TMatrix x1(iR.size(), 1);
    TMatrix x2(iR.size(), 1);
    for (int i = 0 ; i < beta.sizeRow(); i++) {
        beta[i][0] = iR[i];
        x1[i][0] = beta[i][0];
    }
    TMatrix alpha(iR.size());
    alpha = iM;


    for (int i = 0; i < iR.size(); i++) {
        for (int j = 0; j < iR.size(); j++) {
            if (i != j)
                alpha[i][j] = (-1)*alpha[i][j]/alpha[i][i];
        }
        alpha[i][i]=0;
    }
    cout << "alpha:" << endl;
    alpha.print();

    for (int i = 0; i < iR.size(); i++) {
        beta[i][0] = iR[i]/iM[i][i];
        x1[i][0] = beta[i][0];
    }
    cout << endl << "beta: ";
    for (int i = 0; i < beta.sizeRow(); i++) {
        cout << beta[i][0] << " ";
    }
    cout << endl;
    int count = 0;

    double n = alpha.norm();
    double curEps = 1;
    double con = (n/(1-n));
    TMatrix tmpM(beta.sizeRow(), 1);
    if (n < 1) {
        while (curEps > eps) {
            tmpM=alpha*x1;
            for (int i = 0; i < beta.sizeRow(); i++) {
                x2[i][0] = beta[i][0]+tmpM[i][0]; 
            }
            double tmpN1 = 0.0;
            double tmpN2 = 0.0;
            for (int i = 0; i < beta.sizeRow(); i++) {
                if (x1[i][0] < 0) {
                    if ((-1)*x1[i][0] > tmpN1)
                        tmpN1 = (-1)*x1[i][0];
                }
                else {
                    if (x1[i][0] > tmpN1)
                        tmpN1 = x1[i][0];
                }
                if (x2[i][0] < 0) {
                    if ((-1)*x2[i][0] > tmpN2)
                        tmpN2 = (-1)*x2[i][0];
                }
                else {
                    if (x2[i][0] > tmpN2)
                        tmpN2 = x2[i][0];
                }
            }
            tmpN1 -= tmpN2;
            if (tmpN1 < 0)
                tmpN1 *= -1;
            curEps = con*tmpN1;
            ++count;
            x1 = x2;
        }
        cout << endl << "=========================================================" << endl;
        cout << "Count iter: " << count << endl;
        cout << endl;
        x2.print();
        cout << "=========================================================" << endl;
    }
    else {
        cout << "norm > 1" << endl;
    }
}

int main()
{
    cin >> eps;
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

    Solve(A, resA);

    return 0;
}
