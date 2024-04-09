#include <vector>
#include <sstream>
#include <iostream>
#include "Matrix.h"

using namespace std;
template <size_t M, size_t N, typename Field>
std::ostream &operator<<(std::ostream &os, Matrix<N, M, Field> matrix)
{
    vector<vector<Field>> &matrix1 = matrix.GetMatrix();
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            os << matrix1[i][j] << " ";
        }
        os << endl;
    }
    return os;
}