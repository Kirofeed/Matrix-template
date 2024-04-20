#include <iostream>
#include "Matrix.h"
#include <vector>

using namespace std;

int main(){
    vector<vector<double>> vec1 = {
        {-2, 7, -3},
        {4, -14, 6},
        {-3, 7, 13}};
    vector<vector<double>> vec2 = {
        {2, 5, 7}, 
        {6, 3, 4},
        {5, -2, -3}};
    vector<vector<double>> vec3 = {
        {3, 4},
        {5, 7}};

    Matrix<3, 3, double> mat1(vec1);
    Matrix<3, 3, double> mat2 (vec2);
    Matrix<2, 2, double> mat3 (vec3);
    
//    mat1.GaussianMethod();
    vector<double> vec = {1, 2, 3};


    mat2[0][0] = 0;
    cout << mat2 << endl;

    // Matrix<3, double> mat4
}