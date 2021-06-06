#pragma once

#include <cstddef>
#include <iostream>
#include <cassert>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        explicit my_vector();
        explicit my_vector(std::size_t n);
        my_vector(const my_vector& other);

        my_vector& operator=(my_vector other);

        template<typename U>
        friend void swap(my_vector<U>&, my_vector<U>&);

        ~my_vector();

        std::size_t size() const { return size_; }
        std::size_t capacity() const { return capacity_; }
        bool empty() const { return size_ == 0; }

        void resize(std::size_t new_size);
        void reserve(std::size_t new_cap);

        T& operator[](std::size_t index) const;
        void push_back(T t);
        void pop_back();

        void clear();

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const my_vector<U> &mv);

    private:
        void increase_to_power_of_two(std::size_t n) {
            while (capacity_ < n)
                capacity_ <<= 1;
        }
        void delete_by_index(std::size_t index);

    private:
        std::size_t capacity_;
        std::size_t size_;
        char* array_;
    };
}

#include "my_vector_impl.h"
