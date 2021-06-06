#pragma once
#include "huffman_tree.h"
#include <iostream>
#include <fstream>
#include <exception>

namespace Huffman {

    class Encoder {
    public:
        Encoder(std::array<std::string, NUM_BYTES> codes) : codes(codes) {};

        std::string encode(const std::string &str) const noexcept;

    private:
        std::array<std::string, NUM_BYTES> codes;
    };


    class HuffmanArchiver {
    public:
        void archive(std::string input_file, std::string output_file);

    private:
        void read(std::string input_file);

        void write(std::string output_file) const;

    private:
        std::string input;
        FrequencyTable ft;
        std::array<std::string, NUM_BYTES> codes;
    };
}