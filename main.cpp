#include <iostream>
#include "Matrix.h"
#include "outfunk.cpp"

int main()
{
    Matrix<3, 3, double> mat;
    Matrix<3, 3, double> mat1;
    cout << boolalpha << (mat != mat1);
    vector<vector<int> > vec;
    vec.push_back({1, 2, 3, 4, 5});
    Matrix mat2(vec);
    // Matrix<3, 4, double> mat1;
}
