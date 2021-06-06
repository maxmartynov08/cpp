#include "util.h"
#include <cstddef>
#include <fstream>

const std::size_t BYTE_SIZE = 8;

unsigned char convert_to_char(std::string s) noexcept {
    while(s.size() < BYTE_SIZE)
        s.push_back('0');
    unsigned char c = '\0';
    for (std::size_t i = 0; i < BYTE_SIZE; i++)
        c += (s[i] - '0') * (1 << (BYTE_SIZE - 1 - i));
    return c;
}

bool compare_files(std::string path1, std::string path2) noexcept {
    std::ifstream file1(path1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream file2(path2, std::ifstream::binary|std::ifstream::ate);
    if (file1.fail() || file2.fail())
        return false;
    if (file1.tellg() != file2.tellg())
        return false;
    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(file1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(file2.rdbuf()));
}
