#include "matrix.h"
#include <cstring>
#include <cassert>
#include <functional>

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int* [_rows];
    for (int i = 0; i < (int)_rows; i++) {
        _data[i] = new int[_cols];
        std::memset(_data[i], 0, sizeof(int) * _cols);
    }
}

void Matrix::init(const Matrix& m) {
    _rows = m._rows;
    _cols = m._cols;
    _data = new int* [_rows];
    for (int i = 0; i < (int)_rows; i++) {
        _data[i] = new int [_cols];
        std::memcpy(_data[i], m._data[i], sizeof(int) * _cols);
    }
}

Matrix::Matrix(const Matrix& m) {
    init(m);
}

void Matrix::delete_data() {
    for (int i = 0; i < (int)_rows; i++) {
        delete [] _data[i];
        _data[i] = nullptr;
    }
    delete [] _data;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m)
        return *this;
    delete_data();
    init(m);
    return *this;
}

Matrix::~Matrix() {
    delete_data();
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    assert(i < _rows);
    assert(j < _cols);
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    assert(i < _rows);
    assert(j < _cols);
    return _data[i][j];
}

void Matrix::print(FILE* f) const {
    for (int i = 0; i < (int)_rows; i++) {
        for (int j = 0; j < (int)_cols; j++) {
            fprintf(f, "%d", _data[i][j]);
            if (j < (int)_cols - 1)
                fprintf(f, " ");
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols)
        return false;
    for (int i = 0; i < (int)_rows; i++) {
        if (memcmp(_data[i], m._data[i], sizeof(int) * _cols) != 0)
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    *this = *this + m;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    *this = *this - m;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;
    return *this;
}

Matrix Matrix::apply_operation(const Matrix &m, const std::function<int(int, int)> f) const {
    Matrix temp(*this);
    for (int i = 0; i < (int)_rows; i++) {
        for (int j = 0; j < (int)_cols; j++)
            temp._data[i][j] = f(temp._data[i][j], m._data[i][j]);
    }
    return temp;
}

Matrix Matrix::operator+(const Matrix& m) const {
    return apply_operation(m, [](int x, int y){ return x + y; });
}

Matrix Matrix::operator-(const Matrix& m) const {
    return apply_operation(m, [](int x, int y){ return x - y; });
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix temp(_rows, m._cols);
    for (int i = 0; i < (int)_rows; i++) {
        for (int j = 0; j < (int)m._cols; j++) {
            for (int k = 0; k < (int)_cols; k++)
                temp._data[i][j] += _data[i][k] * m._data[k][j];
        }
    }
    return temp;
}
