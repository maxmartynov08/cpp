#include <iostream>
#include <cassert>
#include "my_array.h"

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
}

class NonCopyable {
public:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

template<typename T, std::size_t N, T t>
void my_test_all() {
    my_array<T, N> a;
    assert(a.size() == N);
    a.fill(t);
    for (std::size_t i = 0; i < a.size(); i++)
        assert(a[i] == t);
    a.at(0) = T();
    assert(a.at(0) == T());
    try {
        a.at(N);
    } catch (const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }

    my_array<T, N> b(a);
    for (std::size_t i = 0; i < a.size(); i++)
        assert(a[i] == b[i]);
    b.fill(t);
    for (std::size_t i = 0; i < b.size(); i++)
        assert(b[i] == t);

    const my_array<T, N>& c(b);
    for (std::size_t i = 0; i < c.size(); i++)
        assert(c[i] == t);
    b[0] = T();
    assert(c[0] == T());
}

template<std::size_t N>
void my_test_bool() {
    my_array<bool, N> a;
    for (std::size_t i = 0; i < a.size(); i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;

    a.fill(true);
    for (std::size_t i = 0; i < a.size(); i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;

    my_array<bool, N> b(a);

    b.at(11) = false;

    const my_array<bool, N> c(b);
    for (std::size_t i = 0; i < c.size(); i++)
        std::cout << c.at(i) << ' ';
    std::cout << std::endl;

    a.fill(false);
    for (std::size_t i = 0; i < a.size(); i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;
}

int main() {
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();

    my_test_all<int, 10, 5>();
    my_test_all<bool, 10, true>();

    my_test_bool<20>();
}
