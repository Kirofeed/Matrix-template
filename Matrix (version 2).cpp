#include "Matrix (version 2).h"
#include <iostream>

matrix::matrix() {
	m = 5;
	n = 5;
	p = new double* [m];
	for (int i = 0; i < m; ++i) {
		p[i] = new double[n];
	}
}
matrix::matrix(int m, int n) {
	this->n = n;
	this->m = m;
	p = new double* [m];
	for (int i = 0; i < m; ++i) {
		p[i] = new double[n];
	}
}
matrix::matrix(const matrix& matrix1) {
	this->m = matrix1.m;
	this->n = matrix1.n;
    p = new double* [this->m];
    for (int i = 0; i < this->m; ++i) {
        p[i] = new double[this->n];
    }
    for (int i = 0; i < matrix1.m; ++i) {
        for (int j = 0; j< matrix1.n; ++j) {
            p[i][j] = matrix1.p[i][j];
        }
    }
}
matrix::~matrix() {
    for (int i = 0; i < m; ++i) {
        delete[] p[i];
    }
    delete p;
}

matrix& matrix::operator=(const matrix& matrix1) {
    if (this == &matrix1) {
        return *this;
    }


    for (int i = 0; i < this->m; ++i) {
        delete[] p[i];
    }
    delete[] p;

    this->m = matrix1.m;
    this->n = matrix1.n;
    p = new double*[this->m];
    for (int i = 0; i < this->m; ++i) {
        p[i] = new double[this->n];
    }
    for (int i = 0; i < matrix1.m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            p[i][j] = matrix1.p[i][j];
        }
    }

    return *this;
}


matrix matrix::operator+(const matrix& matrix1) const {
    if (this->m != matrix1.m || this->n != matrix1.n) {
        cerr << "Error: Matrices must have the same dimensions for addition." << endl;
        exit(EXIT_FAILURE);
    }

    matrix result(this->m, this->n);
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            result.p[i][j] = this->p[i][j] + matrix1.p[i][j];
        }
    }
    return result;
}

matrix matrix::operator-(const matrix& matrix1) const {
    if (this->m != matrix1.m || this->n != matrix1.n) {
        cerr << "Error: Matrices must have the same dimensions for addition." << endl;
        exit(EXIT_FAILURE);
    }

    matrix result(this->m, this->n);
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            result.p[i][j] = this->p[i][j] - matrix1.p[i][j];
        }
    }
    return result;
}



ostream& operator << (ostream &os, const matrix &matrix1) {
    for (int i = 0; i < matrix1.m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            cout << matrix1.p[i][j] << "\t";
        }
        cout << endl;
    }
    return os;
}
istream& operator >>(istream &os, const matrix &matrix1) {
    for (int i = 0; i < matrix1.m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            cin >> matrix1.p[i][j];
        }
    }
    return os;
}
matrix& matrix::operator+=(const matrix &matrix1) {
    if (this->m != matrix1.m || this->n != matrix1.n) {
        cerr << "Error: Matrices must have the same dimensions for addition." << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            p[i][j] += matrix1.p[i][j];
        }
    }
    return *this;
}
matrix& matrix::operator-=(const matrix &matrix1) {
    if (this->m != matrix1.m || this->n != matrix1.n) {
        cerr << "Error: Matrices must have the same dimensions for subtraction." << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            p[i][j] -= matrix1.p[i][j];
        }
    }
    return *this;
}
matrix& matrix::operator*=(const matrix &matrix1) {

    auto ** result = new double*[this->m];
    for (int i = 0; i < this->m; ++i) {
        result[i] = new double[matrix1.n];
    }
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < this->n; ++k) {
                result[i][j] += this->p[i][k] * matrix1.p[k][j];
            }
        }
    }
    for (int i = 0; i < this->m; ++i) {
        delete [] p[i];
    }
    delete [] p;

    this->n = matrix1.n;
    p = result;
    return *this;
}
matrix& matrix::operator*=(const double a) {
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->m; ++j) {
            this->p[i][j] = this->p[i][j] * a;
        }
    }
    return *this;
}


matrix matrix::operator*(double a) {
    matrix result(this->m, this->n);
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            result.p[i][j] = this->p[i][j] * a;
        }
    }
    return result;
}
matrix operator*(double a, const matrix& matrix1) {
    matrix result(matrix1.m, matrix1.n);
    for (int i = 0; i < matrix1.m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            result.p[i][j] = a * matrix1.p[i][j];
        }
    }
    return result;
}

matrix matrix::operator*(const matrix& matrix1) const {
    if (this->n != matrix1.m){
        cerr << "Error: Matrices must have special dimensions for multiplication. " << endl;
        exit(EXIT_FAILURE);
    }
    matrix result(this->m, matrix1.n);
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < matrix1.n; ++j) {
            result.p[i][j] = 0;
            for (int k = 0; k < this->n; ++k) {
                result.p[i][j] += this->p[i][k] * matrix1.p[k][j];
            }
        }
    }
    return result;
}


matrix matrix::operator/(double a) {
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            this->p[i][j] = this->p[i][j] / a;
        }
    }
    return *this;
}
bool matrix::operator==(const matrix& matrix1) const {
    if (this == &matrix1) {
        return true;
    }
    else {
        return false;
    }
}
bool matrix::operator!=(const matrix& matrix1) const {
    if (this != &matrix1) {
        return true;
    }
    else {
        return false;
    }
}


