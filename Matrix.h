#pragma once

#include <vector>

using namespace std;

template <size_t M, size_t N, typename Field>
class Matrix
{
    std::vector<std::vector<Field>> matrix;

public:
    Matrix();
    vector<vector<Field>> &GetMatrix();
};