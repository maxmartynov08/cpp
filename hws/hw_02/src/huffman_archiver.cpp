#include "huffman_archiver.h"
#include "util.h"

using namespace Huffman;


std::string Encoder::encode(const std::string &str) const noexcept {
    std::string encoded;
    for (auto c : str)
        encoded += codes[(unsigned char)c];
    return encoded;
}

void HuffmanArchiver::archive(std::string input_file, std::string output_file) {
    try {
        read(input_file);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot read file!\n";
        return;
    }
    ft.build_table(input);
    std::unique_ptr<HuffTree> tree(new HuffTree(ft));
    codes = tree->calc_codes();
    try {
        write(output_file);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot write to file!\n";
        return;
    }
}


void HuffmanArchiver::read(std::string input_file) {
    std::ifstream in(input_file);
    in.exceptions(std::ifstream::failbit);
    in.seekg(0, std::ios::end);
    input.reserve(in.tellg());
    in.seekg(0, std::ios::beg);
    input.assign((std::istreambuf_iterator<char>(in)),
                     std::istreambuf_iterator<char>());
}


void HuffmanArchiver::write(std::string output_file) const {
    std::ofstream out(output_file);
    out.exceptions(std::ofstream::failbit);
    for (auto e : ft.table) {
        out.write(reinterpret_cast<const char *>(&e), sizeof(e));
    }
    Encoder encoder(codes);
    std::string encoded = encoder.encode(input);

    std::size_t extra_bits = (BYTE_SIZE - encoded.length() % BYTE_SIZE) % BYTE_SIZE;
    out.write(reinterpret_cast<const char *>(&extra_bits), sizeof(extra_bits));

    for (std::size_t i = 0; i < encoded.size(); i += BYTE_SIZE) {
        unsigned char byte = convert_to_char(encoded.substr(i, std::min((std::size_t)BYTE_SIZE, encoded.size() - i)));
        out.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
    }
    std::cout << input.size() << '\n' << (encoded.size() + extra_bits) / BYTE_SIZE << '\n' << ft.table.size() * sizeof(ft.table[0]) + sizeof(extra_bits) << std::endl;
}
