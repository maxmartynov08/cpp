#pragma once

#include <algorithm>
#include "my_vector.h"

namespace containers {

    template<typename T>
    my_vector<T>::my_vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = new char[sizeof(T)];
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        capacity_ = 1;
        increase_to_power_of_two(n);
        array_ = new char[capacity_ * sizeof(T)];
        size_ = n;
        for (std::size_t i = 0; i < size_; i++)
            new(array_ + i * sizeof(T)) T();
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = new char[capacity_ * sizeof(T)];
        for(std::size_t i = 0; i < size_; i++) {
            new(array_ + i * sizeof(T)) T(other[i]);
        }
    }

    template<typename T>
    my_vector<T>& my_vector<T>::operator=(my_vector<T> other) {
        swap(*this, other);
        return *this;
    }

    template<typename U>
    void swap(my_vector<U> &mv1, my_vector<U> &mv2) {
        std::swap(mv1.capacity_, mv2.capacity_);
        std::swap(mv1.size_, mv2.size_);
        std::swap(mv1.array_, mv2.array_);
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        clear();
        delete [] array_;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t new_size) {
        if (size_ > new_size) {
            while (size_ > new_size)
                pop_back();
        } else {
            reserve(new_size);
            while (size_ < new_size)
                push_back(T());
        }
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t new_cap) {
        if (new_cap <= capacity_)
            return;
        increase_to_power_of_two(new_cap);
        char *new_array = new char[capacity_ * sizeof(T)];
        for (std::size_t i = 0; i < size_; i++) {
            new(new_array + i * sizeof(T)) T((*this)[i]);
            delete_by_index(i);
        }
        delete [] array_;
        array_ = new_array;
    }

    template<typename T>
    void my_vector<T>::delete_by_index(std::size_t index) {
        ((T*)(array_ + index * sizeof(T)))->~T();
    }

    template<typename T>
    T& my_vector<T>::operator[](std::size_t index) const {
        assert(index < size_);
        return *((T*)(array_ + index * sizeof(T)));
    }

    template<typename T>
    void my_vector<T>::push_back(T t) {
        reserve(size_ + 1);
        new(array_ + size_ * sizeof(T)) T(t);
        size_++;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        assert(size_ > 0);
        delete_by_index(--size_);
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (std::size_t i = 0; i < size_; i++)
            delete_by_index(i);
        size_ = 0;
    }

    template<typename U>
    std::ostream& operator<<(std::ostream& out, const my_vector<U> &mv) {
        for(std::size_t i = 0; i < mv.size(); i++) {
            out << mv[i];
            if(i + 1 < mv.size())
                out << ' ';
        }
        return out;
    }
}
