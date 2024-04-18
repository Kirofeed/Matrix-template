#include <iostream>
#include "Matrix.h"
#include <vector>

using namespace std;

int main(){
    vector<vector<double> > vec1 = {
        {-2, 7, -3},
        {4, -14, 6},
        {-3, 7, 13}};
    vector<vector<int>> vec2 = {
        {1, 2, 3}, 
        {5, 6, 7}, 
        {9, 10, 11}};


    Matrix<3, 3, double> mat1(vec1);
    Matrix<3, 3, int> mat2 (vec2);
    mat1.GaussianMethod();
    cout << mat1 << endl;
}