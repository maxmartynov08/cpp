#include <cstring>
#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
        }

        Product(const Product& other) {
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
        }

        ~Product() {
            delete [] name_;
        }

        friend std::ostream& operator<<(std::ostream& out, const Product& p) {
            out << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
            return out;
        }

    private:
        char *name_;  // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;
    };
}

namespace tests {

    template<typename T>
    void test_my_vector(T t) {
        containers::my_vector<T> mv1;
        assert(mv1.empty());
        assert(mv1.capacity() == 1);

        for (int i = 0; i < 5; i++)
            mv1.push_back(t);
        assert(mv1.size() == 5);
        assert(mv1.capacity() == 8);

        mv1.pop_back();
        assert(mv1.size() == 4);
        assert(mv1.capacity() == 8);

        std::cout << mv1 << std::endl;

        containers::my_vector<T> mv2(mv1);
        mv2.reserve(20);
        mv2.reserve(5);
        assert(mv2.size() == 4);
        assert(mv2.capacity() == 32);

        mv2.clear();
        mv1 = mv2;
        assert(mv1.empty());
        assert(mv1.capacity() == 32);
    }

    template<typename T>
    void test_my_vector_default_constructable() {
        containers::my_vector<T> mv(10);
        assert(mv.size() == 10);
        assert(mv.capacity() == 16);

        mv.resize(5);
        assert(mv.size() == 5);
        assert(mv.capacity() == 16);
        std::cout << mv << std::endl;
    }
}

int main() {
    tests::test_my_vector<int>(5);

    product::Product p("Cookies", 500, 100.0);
    tests::test_my_vector<product::Product>(p);

    tests::test_my_vector_default_constructable<int>();

    return 0;
}
