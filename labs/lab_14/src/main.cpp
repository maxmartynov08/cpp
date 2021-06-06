#include "linq.hpp"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>


using linq::from;

void example1() {
    int xs[] = { 1, 2, 3, 4, 5 };

    std::vector<int> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select([](int x) { return x * x; })  // Возвести в квадрат
                    .where_neq(25)    // Оставить только значения != 25
                    .where([](int x) { return x > 3; })   // Оставить только значения > 3
                    .drop(2)          // Убрать два элемента из начала
                    .to_vector();     // Преобразовать результат в вектор

    std::vector<int> expected = { 16 };
    assert(res == expected);
}

void example2() {
    std::stringstream ss("1 2 3 -1 4");
    std::istream_iterator<int> in(ss), eof;

    std::vector<int> res =
            from(in, eof)  // Взять числа из входного потока
                    .take(4)       // Не более четырёх чисел
                    .until_eq(-1)  // Перестать читать после прочтения -1
                    .to_vector();  // Получить список считанных чисел

    std::vector<int> expected = { 1, 2, 3 };
    assert(expected == res);

    int remaining;
    assert(ss >> remaining);
    assert(remaining == 4);
}

void example3() {
    int xs[] = { 1, 2, 3, 4, 5 };

    std::vector<double> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
                    .to_vector();     // Преобразовать результат в вектор

    assert(res.size() == 5);
    for (std::size_t i = 0; i < res.size(); i++) {
        assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
    }
}

void example4() {
    std::stringstream iss("4 16");
    std::stringstream oss;
    std::istream_iterator<int> in(iss), eof;
    std::ostream_iterator<double> out(oss, "\n");

    from(in, eof)    // Взять числа из входного потока
            .select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); })  // Извлечь из каждого корень
            .copy_to(out);  // Вывести на экран

    assert(oss.str() == "2\n4\n");
}


void my_test() {
    int xs[] = { 4, 1, 2, 3, 4, 5 };
    auto f = [](int x) { return x > 3; };

    std::vector<int> res =
            from(xs, xs + 6)
            .where(f)
            .to_vector();


    std::vector<int> res2 =
            from(xs, xs + 6)
                    .where_neq(1)
                    .where_neq(2)
                    .where_neq(3)
                    .to_vector();

    std::vector<int> gg;
    std::vector<int> res3 = from(gg.begin(), gg.end()).select([](int x) { return x + 3; }).to_vector();
    assert(res3 == gg);

    std::vector<int> expected = {4, 4, 5};
    assert(res == expected);
    //assert(res1 == expected);
    assert(res2 == expected);

}

void empty_select() {
    std::vector<int> emp;
    auto res1 = from(emp.begin(), emp.end()).select([](int x) { return x + 1; })
            .to_vector();
    assert(res1 == emp);

    int xs[] = {1, 2, 3, 4, 5};
    auto res = from(xs, xs+5).select<double>([](int x) { return sqrt(x); })
            .to_vector();
}

template<typename F>
struct NonCopyableFunctorWrapper {
    NonCopyableFunctorWrapper(F &&other) : f_(new F(std::move(other))) {}
    NonCopyableFunctorWrapper(const NonCopyableFunctorWrapper &other) : f_(new F(*other.f_.get())) {
        std::cout << "Unexpected copy\n";
    }
    NonCopyableFunctorWrapper(NonCopyableFunctorWrapper &&other) = default;
    NonCopyableFunctorWrapper& operator=(NonCopyableFunctorWrapper other) {
        f_.swap(other.f_);
    }

    template<typename... Args>
    auto operator()(Args... args) {
        assert(f_);
        return (*f_)(std::forward<Args>(args)...);
    }

    template<typename... Args>
    auto operator()(Args... args) const {
        assert(f_);
        return static_cast<const F&>(*f_)(std::forward<Args>(args)...);
    }

private:
    std::unique_ptr<F> f_;
};

template<typename F>
auto force_move(F &&f) {
    return NonCopyableFunctorWrapper<F>(std::move(f));
}


void gg_wp_test() {
    auto xs = std::vector < int > {9, 4, 8, 1, -3, 8, 7};

    auto res = from(xs.begin(), xs.end()).select(force_move([](int x) { return x + 3; })).to_vector();
    assert((std::vector < int > {12, 7, 11, 4, 0, 11, 10}) == res);
    auto res1 = from(xs.begin(), xs.end()).where(force_move([](int x) { return x < 0; })).to_vector();

    assert((std::vector < int > {-3}) == res1);

    auto res2 = from(xs.begin(), xs.end()).until(force_move([](int x) { return x < 0; })).to_vector();

    assert((std::vector < int > {9, 4, 8, 1}) == res2);
}

int main() {
    example1();
    example2();
    example3();
    example4();
    my_test();
    empty_select();
    gg_wp_test();
    return 0;
}