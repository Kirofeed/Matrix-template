#include <iostream>
#include <sstream>


using namespace std;

template <size_t N, size_t M, typename Field>
class Matrix {
    protected:
    vector<vector<Field> > data;
    public:
    Matrix();
    template <size_t N1, size_t M1, typename Field1>
    bool operator==(const Matrix<N1, M1, Field1>& other) const;
    template <size_t N1, size_t M1, typename Field1>
    bool operator!=(const Matrix<N1, M1, Field1>& other) const;

    friend ostream& operator<<(ostream& os, const Matrix<N, M, Field>& mat) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                os << mat.data[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
};

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix() {
    data.resize(N);
    for (size_t i = 0; i < N; i++)
    {
        data[i].resize(M);
    }
    
    if (N == M) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                if (i == j) {
                    data[i][j] = Field(1);
                } else {
                    data[i][j] = Field(0);
                }   
            }
        }
    }
    else {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                data[i][j] = Field(0);
            }
        }
    }
}

template <size_t N, size_t M, typename Field>
template <size_t N1, size_t M1, typename Field1>
bool Matrix<N, M, Field>::operator==(const Matrix<N1, M1, Field1>& other) const {
    if (N != N1 || M != M1 || typeid(Field) != typeid(Field1)) 
    {
       return false;
    }
    
    if (this->data == other.data) {
        return true;
    }
    return false;
}

template <size_t N, size_t M, typename Field>
template <size_t N1, size_t M1, typename Field1>
bool Matrix<N, M, Field>::operator!=(const Matrix<N1, M1, Field1>& other) const {
    if (N != N1 || M != M1 || typeid(Field) != typeid(Field1)) 
    {
       return true;
    }
    if (this->data != other.data) {
        return true;
    }
    return false;
}