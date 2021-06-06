#pragma once
#include "huffman_tree.h"
#include <iostream>
#include <fstream>
#include <exception>

namespace Huffman {

    class HuffmanUnarchiver {
    public:
        void unarchive(std::string input_file, std::string output_file);

    private:
        void read(std::string input_file);

        void decode_and_write(std::string output_file) const;

    private:
        FrequencyTable ft;
        std::size_t extra_bits;
        std::string encoded;
        std::array<std::string, NUM_BYTES> codes;
    };
}
