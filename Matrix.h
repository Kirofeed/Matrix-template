#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

template <size_t N, size_t M, typename Field>
class Matrix {
protected:
    vector<vector<Field> > data;
    public:
    Matrix();
    Matrix(const vector<vector<Field> >& data);
    template <size_t N1, size_t M1, typename Field1>
    bool operator==(const Matrix<N1, M1, Field1>& other) const;
    template <size_t N1, size_t M1, typename Field1>
    bool operator!=(const Matrix<N1, M1, Field1>& other) const;
    Matrix<N, M, Field>& operator+=(const Matrix<N, M, Field>& other);
    Matrix<N, M, Field>& operator-=(const Matrix<N, M, Field>& other);
    Matrix<N, M, Field> operator+(const Matrix<N, M, Field>& other) const;
    Matrix<N, M, Field> operator-(const Matrix<N, M, Field>& other) const;
    Matrix<N, M, Field>& operator*(const Field& num);
    template <size_t N1, size_t M1, typename Field1>    
    typename enable_if<(N == N1 && M == M1 && Field == Field1), Matrix<N, M, Field>&>::type 
    operator*=(const Matrix<N1, M1, Field1>& other);
    template <size_t N1, size_t M1, typename Field1>    
    typename enable_if<(M == N1 && Field == Field1), Matrix<N, M1, Field>&>::type 
    operator*(const Matrix<N1, M1, Field1>& other);



    vector<vector<Field> > GetData() const {
        return data;
    }

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
Matrix<N, M, Field>::Matrix(const vector<vector<Field> >& data) : Matrix() {
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            this->data[i][j] = data[i][j];
        }
    }
}


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
    if (N != N1 || M != M1 || typeid(Field) != typeid(Field1)) {
       return false; // если размеры или типы отличаются, то матрицы точно не равны
    }
    if (this->data == other.GetData()) {
        return true; // если данные различаются, то матрицы не равны
    }
    return false; // если все проверки пройдены, матрицы равны
}

template <size_t N, size_t M, typename Field>
template <size_t N1, size_t M1, typename Field1>
bool Matrix<N, M, Field>::operator!=(const Matrix<N1, M1, Field1>& other) const {
    if (N != N1 || M != M1 || typeid(Field) != typeid(Field1)) {
       return true; // если размеры или типы отличаются, то матрицы точно не равны
    }
    if (this->data != other.GetData()) {
        return true; // если данные различаются, то матрицы не равны
    }
    return false; // если все проверки пройдены, матрицы равны
}

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator+=(const Matrix<N, M, Field>& other) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}   

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator-=(const Matrix<N, M, Field>& other) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
} 

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator+(const Matrix<N, M, Field>& other) const {
    Matrix<N, M, Field> result = *this;
    result += other;
    return result;
}

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator-(const Matrix<N, M, Field>& other) const {
    Matrix<N, M, Field> result = *this;
    result -= other;
    return result;
}


template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator*(const Field& num) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            data[i][j] *= num;
        }
    }
    return *this;
}

template <size_t N, size_t M, typename Field>    
template <size_t N1, size_t M1, typename Field1>    
typename enable_if<(N == N1 && M == M1 && Field == Field1), Matrix<N, M, Field>&>::type 
Matrix<N, M, Field>::operator*=(const Matrix<N1, M1, Field1>& other) {
    Matrix<N, M, Field> newMat;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M1; j++)
        {
            newMat.data[i][j] = 0;
            for (size_t k = 0; k < M; k++)
            {
                newMat.data[i][j] += (this->data[i][k] * other.data[k][j]);
            }
        }
    }
    *this = newMat;
    return *this;
}


template <size_t N, size_t M, typename Field>    
template <size_t N1, size_t M1, typename Field1>    
typename enable_if<M == N1 && Field == Field1, Matrix<N, M1, Field>&>::type 
Matrix<N, M, Field>::operator*(const Matrix<N1, M1, Field1>& other) {
    Matrix<N, M1, Field> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M1; j++) {
            result.data[i][j] = 0;
            for (size_t k = 0; k < M; k++) {
                result.data[i][j] += (data[i][k] * other.data[k][j]);
            }
        }
    }
    return result;
}

