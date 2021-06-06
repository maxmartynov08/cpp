#include <cassert>
#include <algorithm>
#include "my_vector.h"

const std::size_t DEFAULT_CAPACITY = 2;

MyVector::MyVector() {
    *this = MyVector(DEFAULT_CAPACITY);
}

MyVector::MyVector(std::size_t init_capacity) {
    _cp = init_capacity;
    _sz = 0;
    _data = new int[_cp];
}

MyVector::MyVector(const MyVector& another_vector) {
    _cp = another_vector._cp;
    _sz = another_vector._sz;
    _data = new int[_cp];
    std::memcpy(_data, another_vector._data, sizeof(int) * _sz);
}

MyVector::~MyVector() {
    delete [] _data;
    _data = nullptr;
}

MyVector& MyVector::operator=(const MyVector &another_vector) {
    if (&another_vector == this)
        return *this;
    delete [] _data;
    _cp = another_vector._cp;
    _sz = another_vector._sz;
    _data = new int[_cp];
    std::memcpy(_data, another_vector._data, sizeof(int) * _sz);
    return *this;
}

void MyVector::set(std::size_t index, int value) {
    assert(index < _sz);
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    assert(index < _sz);
    return _data[index];
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity < _cp)
        return;
    int* new_data = new int[new_capacity];
    std::memcpy(new_data, _data, sizeof(int) * _cp);
    delete [] _data;
    _data = new_data;
    _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if (_cp < new_size)
        reserve(std::max(2 * _cp, new_size));
    if (_sz < new_size)
        std::memset(_data + _sz, 0, sizeof(int) * (new_size - _sz));
    _sz = new_size;
}

void MyVector::push_back(int value) {
    if (_sz == _cp)
        reserve(2 * _cp);
    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
    assert(index <= _sz);
    if (_sz == _cp)
        reserve(2 * _cp);
    std::memmove(_data + index + 1, _data + index, sizeof(int) * (_sz - index));
    _data[index] = value;
    _sz++;
}

void MyVector::erase(std::size_t index) {
    assert(index < _sz);
    std::memmove(_data + index, _data + index + 1, sizeof(int) * (_sz - index - 1));
    _sz--;
}
