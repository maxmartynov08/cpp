#ifndef LAB_10_UTIL_H
#define LAB_10_UTIL_H

#include <cstdint>
#include <fstream>

inline int32_t read_int_from_file(std::ifstream& in) {
    int32_t x;
    in.read((char*)&x, sizeof x);
    return x;
}

inline void print_int_to_file(std::ofstream& out, int32_t x) {
    out.write((char*)&x, sizeof x);
}

#endif //LAB_10_UTIL_H
