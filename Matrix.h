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
    typename enable_if<(N == N1 && M == M1 && is_same<Field, Field1>::value), Matrix<N, M, Field>&>::type 
    operator*=(const Matrix<N1, M1, Field1>& other);
    template <size_t N1, size_t M1, typename Field1>    
    typename enable_if<(M == N1 && is_same<Field, Field1>::value), Matrix<N, M1, Field>>::type 
    operator*(const Matrix<N1, M1, Field1>& other);
    typename enable_if<(N == M), Field>::type
    det() const;
    Matrix<M, N, Field> transposed();
    size_t rank() const;
    void GaussianMethod();


    void SetData(const vector<vector<Field> >& data) {
        this->data = data;
    }

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
typename enable_if<(N == N1 && M == M1 && is_same<Field, Field1>::value), Matrix<N, M, Field>&>::type 
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
typename enable_if<M == N1 && is_same<Field, Field1>::value, Matrix<N, M1, Field>>::type 
Matrix<N, M, Field>::operator*(const Matrix<N1, M1, Field1>& other) {
    Matrix<N, M1, Field> newMat;
    auto new_data = newMat.GetData();
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M1; j++)
        {
            new_data[i][j] = 0;
            for (size_t k = 0; k < M; k++)
            {
                new_data[i][j] += (this->data[i][k] * other.GetData()[k][j]);
            }
        }
    }
    newMat.SetData(new_data);
    return newMat;
}

template <size_t N, size_t M, typename Field>  
typename enable_if<(N == M), Field>::type
Matrix<N, M, Field>::det() const {
    Matrix<N, M, Field> temp(*this);  // Create a copy of the matrix
    Field det = 1;
    for (size_t i = 0; i < N; i++) {
        // Find the maximum element in the current column
        size_t max_row = i;
        for (size_t j = i + 1; j < N; j++) {
            if (abs(temp.data[j][i]) > abs(temp.data[max_row][i])) {
                max_row = j;
            }
        }

        // Swap the maximum row with the current row
        if (i != max_row) {
            swap(temp.data[i], temp.data[max_row]);
            det *= -1;  // Change the sign of the determinant
        }

        // Make all rows below this one 0 in the current column
        for (size_t j = i + 1; j < N; j++) {
            Field factor = temp.data[j][i] / temp.data[i][i];
            for (size_t k = i; k < N; k++) {
                temp.data[j][k] -= factor * temp.data[i][k];
            }
        }

        det *= temp.data[i][i];
    }

    return det;
}


template <size_t N, size_t M, typename Field>
Matrix<M, N, Field> Matrix<N, M, Field>::transposed() {
    Matrix<M, N, Field> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            result.data[j][i] = this->data[i][j];
        }
    }
    return result;
}


template <size_t N, size_t M, typename Field>
size_t Matrix<N, M, Field>::rank() const {
    Matrix<N, M, Field> temp(*this);  // Create a copy of the matrix
    size_t rank = 0;
    for (size_t i = 0; i < N; i++) {
        // Find the maximum element in the current column
        size_t max_row = i;
        for (size_t j = i + 1; j < N; j++) {
            if (abs(temp.data[j][i]) > abs(temp.data[max_row][i])) {
                max_row = j;
            }
        }

        // Swap the maximum row with the current row
        if (i != max_row) {
            swap(temp.data[i], temp.data[max_row]);
        }

        // If the leading coefficient is zero, skip this row
        if (temp.data[i][i] == 0) {
            continue;
        }

        // Make all rows below this one 0 in the current column
        for (size_t j = i + 1; j < N; j++) {
            Field factor = temp.data[j][i] / temp.data[i][i];
            for (size_t k = i; k < M; k++) {
                temp.data[j][k] -= factor * temp.data[i][k];
            }
        }

        // If the row is not all zeros, increase the rank
        for (size_t j = 0; j < M; j++) {
            if (temp.data[i][j] != 0) {
                rank++;
                break;
            }
        }
    }

    return rank;
}

template <size_t N, size_t M, typename Field>
void Matrix<N, M, Field>::GaussianMethod() {
    for (size_t i = 0; i < N; i++) {
        // Find the maximum element in the current column
        size_t max_row = i;
        for (size_t j = i + 1; j < N; j++) {
            if (abs(data[j][i]) > abs(data[max_row][i])) {
                max_row = j;
            }
        }

        // Swap the maximum row with the current row
        if (i != max_row) {
            swap(data[i], data[max_row]);
        }

        // If the leading coefficient is zero, skip this row
        if (data[i][i] == 0) {
            continue;
        }

        // Make all rows below this one 0 in the current column
        for (size_t j = i + 1; j < N; j++) {
            Field factor = data[j][i] / data[i][i];
            for (size_t k = i; k < M; k++) {
                data[j][k] -= factor * data[i][k];
            }
        }
    }
}
