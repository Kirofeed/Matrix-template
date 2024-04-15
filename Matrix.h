#pragma once

#include <vector>

using namespace std;


template <size_t M, size_t N, typename Field>
class Matrix
{
private:
    size_t m;
    size_t n;
    std::vector<std::vector<Field> > matrix;
    
public:
    Matrix() = delete;
    Matrix(vector<vector<Field> > &vec) : m(M), n(N), matrix(vec){}
    vector<vector<Field> > &GetMatrix()
    {
        return this->matrix;
    }

    bool operator==(Matrix other) {
        return (this->matrix == other.matrix);
    }

    bool operator!=(Matrix other)
    {
        return (this->matrix != other.matrix);
    }
};

template <size_t M, typename Field>
class Matrix<M, M, Field>{
private:
    size_t m;
    std::vector<std::vector<Field> > matrix;

public:
    Matrix() : m(M), matrix(m, std::vector<Field>(m))
    {
        for (size_t i = 0; i < m; ++i){
            for (size_t j = 0; j < m; ++j){
                if (i == j){
                    this->matrix[i][j] = Field(1);
                }
                else
                {
                    this->matrix[i][j] = Field(0);
                }
            }
        }
    }
    vector<vector<Field> > &GetMatrix()
    {
        return this->matrix;
    }

    bool operator==(Matrix other)
    {
        return (this->matrix == other.matrix);
    }

    bool operator!=(Matrix other)
    {
        return (this->matrix != other.matrix);
    }
};