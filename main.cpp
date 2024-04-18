#include <iostream>
#include "Matrix.h"
#include <vector>

using namespace std;

int main(){
    vector<vector<int> > vec;
    vector<int> vec1;
    vector<int> vec2;
    vector<int> vec3;

    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    vec3.push_back(7);
    vec3.push_back(8);
    vec3.push_back(9);
    vec.push_back(vec1);
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
     vec.push_back(vec2);
    vec.push_back(vec3);

    Matrix<3, 3, int> mat(vec);
    Matrix<3, 4, int> mat1;

    cout  << (mat *= mat1) << endl;
    // cout << mat << endl;
}