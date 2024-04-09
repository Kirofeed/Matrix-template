#include "Matrix.h"
#include <vector>

using namespace std;

template <size_t M, size_t N, typename Field>
vector<vector<Field>> &Matrix<M, N, Field>::GetMatrix()
{
    return this.matrix;
}