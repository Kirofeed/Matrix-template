#pragma once
#include <iostream>
using namespace std;
class matrix
{
    friend matrix operator*(double a, const matrix& matrix1);
    friend ostream& operator <<(ostream& os, const matrix &matrix1);
    friend istream& operator >>(istream& os, const matrix &matrix1);
	int m, n;
	double** p;
public:
	matrix();
	matrix(int m, int n);
	matrix(const matrix& matrix1);
	~matrix();
    matrix& operator=(const matrix& matrix1);
    matrix operator+(const matrix& matrix1) const;
    matrix operator-(const matrix& matrix1) const;
    matrix& operator+=(const matrix &matrix1);
    matrix& operator-=(const matrix &matrix1);
    matrix& operator*=(const matrix &matrix1);
    matrix& operator*= (double a);
    matrix operator*(double a);
    matrix operator*(const matrix& matrix1) const;
    matrix operator/(double a);
    bool operator==(const matrix& matrix1) const;
    bool operator!=(const matrix& matrix1) const;

};