#include "matrix.h"
#include <cstring>
#include <cassert>

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int* [_rows];
    for (int i = 0; i < (int)_rows; i++) {
        _data[i] = new int[_cols];
        std::memset(_data[i], 0, sizeof(int) * _cols);
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < (int)_rows; i++) {
        delete [] _data[i];
        _data[i] = nullptr;
    }
    delete [] _data;
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
