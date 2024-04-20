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
    explicit Matrix(const vector<vector<Field> >& data);
    template <size_t N1, size_t M1, typename Field1>
    bool operator==(const Matrix<N1, M1, Field1>& other) const;
    template <size_t N1, size_t M1, typename Field1>
    bool operator!=(const Matrix<N1, M1, Field1>& other) const;
    Matrix<N, M, Field>& operator+=(const Matrix<N, M, Field>& other);
    Matrix<N, M, Field>& operator-=(const Matrix<N, M, Field>& other);
    Matrix<N, M, Field> operator+(const Matrix<N, M, Field>& other) const;
    Matrix<N, M, Field> operator-(const Matrix<N, M, Field>& other) const;
    Matrix<N, M, Field> operator*(const Field& num);
    Matrix<N, M, Field>& operator*=(const Field& num);
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
    typename enable_if<N == M, Field>::type
    trace();
    typename enable_if<N == M, Matrix<N, M, Field>>::type
    inverted() const;
    typename enable_if<N == M, Matrix<N, M, Field>&>::type
    invert();
    vector<Field> getRow(size_t i);
    vector<Field> getColumn(size_t i);
    vector<Field>& operator[](size_t);
    const vector<Field>& operator[](size_t) const;



    void SetData(const vector<vector<Field> >& vec) {
        this->data = vec;
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
Matrix<N, M, Field> Matrix<N, M, Field>::operator*(const Field& num) {
    Matrix<N, M, Field> result = *this;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            result.data[i][j] *= num;
        }
    }
    return result;
}

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator*=(const Field& num) {
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
typename enable_if<(M == N1 && is_same<Field, Field1>::value), Matrix<N, M1, Field>>::type
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
    vector<vector<Field>> tmp = this->data;
    double det = 1.0;

    for (size_t i = 0; i < N; ++i) {
        // Поиск максимального элемента в столбце
        size_t pivot_row = i;
        for (size_t j = i + 1; j < N; ++j) {
            if (abs(tmp[j][i]) > abs(tmp[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            swap(tmp[i], tmp[pivot_row]);
            // При смене строк меняется знак определителя
            det *= -1.0;
        }
        // Если главный элемент равен нулю, определитель равен нулю
        if (tmp[i][i] == 0.0)
            return 0.0;
        // Приведение матрицы к треугольному виду
        for (size_t j = i + 1; j < N; ++j) {
            double ratio = tmp[j][i] / tmp[i][i];
            for (size_t k = i; k < N; ++k) {
                tmp[j][k] -= ratio * tmp[i][k];
            }
        }
        // Умножение диагональных элементов для получения определителя
        det *= tmp[i][i];
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


template <size_t N, size_t M, typename Field>
typename enable_if<N == M, Field>::type
Matrix<N, M, Field>::trace() {
    Field trace = Field(0);
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            if (i == j) {
                trace += this->data[i][j];
            }
        }
        
    }
    return trace;
}


template <size_t N, size_t M, typename Field>
typename enable_if<N == M, Matrix<N, M, Field>>::type
Matrix<N, M, Field>::inverted() const {
    Matrix<N, M, Field> inverseMatrix;

    // Копирование исходной матрицы во временную матрицу
    vector<vector<Field>> tmp = this->data;

    // Единичная матрица, которую будем преобразовывать к обратной
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i == j)
                inverseMatrix.data[i][j] = Field(1);
            else
                inverseMatrix.data[i][j] = Field(0);
        }
    }

    // Прямой ход метода Гаусса-Жордана
    for (size_t i = 0; i < N; ++i) {
        // Поиск главного элемента для текущей строки
        size_t pivot_row = i;
        for (size_t j = i + 1; j < N; ++j) {
            if (abs(tmp[j][i]) > abs(tmp[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            swap(tmp[i], tmp[pivot_row]);
            swap(inverseMatrix.data[i], inverseMatrix.data[pivot_row]);
        }
        // Деление текущей строки на главный элемент
        double pivot = tmp[i][i];
        for (size_t j = 0; j < N; ++j) {
            tmp[i][j] /= pivot;
            inverseMatrix.data[i][j] /= pivot;
        }
        // Вычитание текущей строки из остальных строк
        for (size_t j = 0; j < N; ++j) {
            if (j != i) {
                double ratio = tmp[j][i];
                for (size_t k = 0; k < N; ++k) {
                    tmp[j][k] -= ratio * tmp[i][k];
                    inverseMatrix.data[j][k] -= ratio * inverseMatrix.data[i][k];
                }
            }
        }
    }
    return inverseMatrix;
}


template <size_t N, size_t M, typename Field>
typename enable_if<N == M, Matrix<N, M, Field>&>::type
Matrix<N, M, Field>::invert() {
    return *this = this->inverted();
}

template <size_t N, size_t M, typename Field>
vector<Field> Matrix<N, M, Field>::getRow(size_t i) {
    return data[i];
}

template <size_t N, size_t M, typename Field>
vector<Field> Matrix<N, M, Field>::getColumn(size_t i) {
    vector<Field> column;
    for (size_t j = 0; j < N; j++)
    {
        column.push_back(data[j][i]);
    }
    return column;
}

template <size_t N, size_t M, typename Field>
vector<Field>& Matrix<N, M, Field>::operator[](size_t i) {
    return data[i];
}

template <size_t N, size_t M, typename Field>
const vector<Field>& Matrix<N, M, Field>::operator[](size_t) const {
    return data[i];
}

