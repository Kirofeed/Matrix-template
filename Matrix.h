#include "vector"
#include <sstream>
#include <iostream>

using namespace std;

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child >
class BaseMatrix {
public:
    Child<N, M, Field> &operator+=(Child<N, M, Field> other);
    Child<N, M, Field> operator+(Child<N, M, Field> other);
    Child<N, M, Field> &operator-=(Child<N, M, Field> other);
    Child<N, M, Field> operator-(Child<N, M, Field> other);
    Child<N, M, Field> operator*(Field num);
    template <size_t A>
    Child<N, A, Field> operator*(const Child<M, A, Field> &other);
protected:
    BaseMatrix(vector<vector<Field>> oth_vec) : BaseMatrix<N, M, Field, Child>::BaseMatrix()
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                vec[i][j] = oth_vec[i][j];
            }
        }
    }
    vector<vector<Field> > vec;
    BaseMatrix()
    {
        vec.resize(N);
        for (size_t i = 0; i < N; i++)
        {
            vec[i].resize(M);
        }
    }

public:
    bool operator==(BaseMatrix<N, M, Field, Child> &other);
    bool operator!=(BaseMatrix<N, M, Field, Child> &other);
    template <size_t X, size_t Y, typename Z, template <size_t, size_t, typename> typename F>
    friend ostream& operator<<(ostream& os, BaseMatrix<X, Y, Z, F> matrix);
   
};

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> &BaseMatrix<N, M, Field, Child>::operator+=(Child<N, M, Field> other)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            this->vec[i][j] += other.vec[i][j];
        }
    }
    return *(static_cast<Child<N, M, Field>*>(this));
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> BaseMatrix<N, M, Field, Child>::operator+(Child<N, M, Field> other)
{
    BaseMatrix newMat(*this);
    return (newMat += other);
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> &BaseMatrix<N, M, Field, Child>::operator-=(Child<N, M, Field> other)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            this->vec[i][j] -= other.vec[i][j];
        }
    }
    return *(static_cast<Child<N, M, Field> *>(this));
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> BaseMatrix<N, M, Field, Child>::operator-(Child<N, M, Field> other)
{
    BaseMatrix newMat(*this);
    return (newMat -= other);
}

template <size_t N, size_t M, typename Field, template<size_t, size_t, typename> typename Child>
Child<N, M, Field> BaseMatrix<N, M, Field, Child>::operator*(Field num) {
    for (size_t i = 0; i < N; i++) 
    {
        for (size_t j = 0; j < M; j++) 
        {
            this->vec[i][j] *= num;
        }
    }
    return *(static_cast<Child<N, M, Field> *>(this));
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
template <size_t A>
Child<N, A, Field> BaseMatrix<N, M, Field, Child>::operator*(const Child<M, A, Field> &other)
{
    BaseMatrix<N, A, Field, Child> newMat;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < A; j++)
        {
            for (size_t k = 0; k < M; k++)
            {
                newMat.vec[i][j] += (this->vec[i][k] * other.vec[k][j]);
            } 
            
        }
    }
    return *(static_cast<Child<N, A, Field> *>(&newMat));
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
bool BaseMatrix<N, M, Field, Child>::operator==(BaseMatrix<N, M, Field, Child> &other)
{
    return this->vec == other.vec;
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
bool BaseMatrix<N, M, Field, Child>::operator!=(BaseMatrix<N, M, Field, Child> &other)
{
    return this->vec != other.vec;
}

template <size_t X, size_t Y, typename Z, template <size_t, size_t, typename> typename F>
ostream& operator<<(ostream& os, BaseMatrix<X, Y, Z, F> matrix) {
    for (size_t i = 0; i < X; i++)
    {
        for (size_t j = 0; j < Y; j++)
        {
            os << matrix.vec[i][j] << "\t";
        }
        os << "\n";
    }
    return os;
}

template <size_t N, size_t M, typename Field>
class Matrix : public BaseMatrix<N, M, Field, Matrix>
{
public:
    Matrix(vector<vector<Field>> oth_vec) : BaseMatrix<N, M, Field, Matrix>::BaseMatrix()
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                vec[i][j] = oth_vec[i][j];
            }
        }
    }
    Matrix();
};

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix() : BaseMatrix<N, M, Field, Matrix>::BaseMatrix() {}

template <size_t N, typename Field>
class Matrix<N, N, Field> : public BaseMatrix<N, N, Field, Matrix> {
public:
    Matrix(vector<vector<Field>> oth_vec) : BaseMatrix<N, N, Field, Matrix>::BaseMatrix()
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                vec[i][j] = oth_vec[i][j];
            }
        }
    }
    Matrix();
};

template <size_t N, typename Field>
Matrix<N, N, Field>::Matrix() : BaseMatrix<N, N, Field, Matrix>::BaseMatrix()
{
    for (size_t i = 0; i < N; i++) {
        this->vec[i][i] = Field(1);
    }
}
