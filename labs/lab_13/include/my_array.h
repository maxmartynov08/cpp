#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstdint>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    public:
        T& at(std::size_t index) {
            if (index >= size())
                throw std::out_of_range("Index out of range");
            return _data[index];
        }
        const T& at(std::size_t index) const {
            if (index >= size())
                throw std::out_of_range("Index out of range");
            return _data[index];
        }

        T& operator[](std::size_t index) noexcept {
            return _data[index];
        }
        const T& operator[](std::size_t index) const noexcept {
            return _data[index];
        }

        bool empty() const noexcept {
            return size() == 0;
        }
        std::size_t size() const noexcept {
            return N;
        }

        void fill(const T &val) noexcept {
            for (std::size_t i = 0; i < N; i++)
                _data[i] = val;
        }

    private:
        T _data[N];
    };

    class proxy {
    private:
        uint8_t& _data;
        uint8_t _mask;

    public:
        proxy(uint8_t& data, uint8_t mask) : _data(data), _mask(mask) {};
        operator bool() const {
            return _data & _mask;
        }

        proxy& operator=(bool val) {
            val ? _data |= _mask : _data &= ~_mask;
            return *this;
        }

        proxy& operator=(const proxy& other) {
            *this = (bool)other;
            return *this;
        }
    };

    template<std::size_t N>
    class my_array<bool, N> {
    public:
        proxy at(std::size_t index) {
            if (index >= size())
                throw std::out_of_range("Index out of range");
            return proxy(_data[index / _base], 1 << (index % _base));
        }
        bool at(std::size_t index) const {
            if (index >= size())
                throw std::out_of_range("Index out of range");
            return get(index);
        }

        proxy operator[](std::size_t index) noexcept {
            return proxy(_data[index / _base], 1 << (index % _base));
        }

        bool operator[](std::size_t index) const noexcept {
            return get(index);
        }

        bool empty() const noexcept {
            return size() == 0;
        }
        std::size_t size() const noexcept {
            return N;
        }

        void fill(bool val) noexcept {
            for (std::size_t i = 0; i < N; i++)
                (*this)[i] = val;
        }

    private:
        bool get(std::size_t index) const {
            return _data[index / _base] & (1 << (index % _base));
        }

    private:
        static const std::size_t _base = 8;
        uint8_t _data[(N + _base - 1) / _base]{};
    };
}
