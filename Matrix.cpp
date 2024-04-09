
#include "Matrix.h"

template <size_t M, size_t N, typename Field>
Matrix<M, N, Field>::Matrix()
{
    if (N == M)
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                if (i == j)
                {
                    this.matrix[i][j] = 1;
                }
                else
                {
                    this.matrix[i][j] = 0;
                }
            }
        }
    }
    else
    {
        return;
    }
}