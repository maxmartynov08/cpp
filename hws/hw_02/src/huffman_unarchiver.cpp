#include "huffman_unarchiver.h"
#include <unordered_map>

using namespace Huffman;


void HuffmanUnarchiver::unarchive(std::string input_file, std::string output_file) {
    try {
        read(input_file);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot read file!\n";
        return;
    }
    std::unique_ptr<HuffTree> tree(new HuffTree(ft));
    codes = tree->calc_codes();
    try {
        decode_and_write(output_file);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot write to file!\n";
        return;
    }
}

void HuffmanUnarchiver::read(std::string input_file) {
    std::ifstream in(input_file);
    in.exceptions(std::ifstream::failbit);

    for (std::size_t i = 0; i < NUM_BYTES; i++) {
        in.read(reinterpret_cast<char *>(&ft.table[i]), sizeof(ft.table[i]));
    }
    in.read(reinterpret_cast<char *>(&extra_bits), sizeof(extra_bits));

    auto cur_pos = in.tellg();
    in.seekg(0, std::ios::end);
    encoded.reserve(in.tellg() - cur_pos);
    in.seekg(cur_pos);
    encoded.assign((std::istreambuf_iterator<char>(in)),
                   std::istreambuf_iterator<char>());
}

void HuffmanUnarchiver::decode_and_write(std::string output_file) const {
    std::ofstream out(output_file);
    out.exceptions(std::ofstream::failbit);

    std::unordered_map<std::string, char> symbols;
    for (std::size_t i = 0; i < codes.size(); i++)
        symbols[codes[i]] = i;

    std::string cur_code;
    std::size_t cnt_bytes = 0;
    for (std::size_t i = 0; i < encoded.size(); i++) {
        for (int pos = BYTE_SIZE - 1; pos >= 0; pos--) {
            if (i == encoded.size() - 1 && (std::size_t)pos < extra_bits)
                break;
            cur_code += ((((unsigned char)encoded[i] >> pos) & 1) ? "1" : "0");
            if (symbols.find(cur_code) != symbols.end()) {
                char byte = symbols[cur_code];
                out.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
                cur_code.clear();
                cnt_bytes++;
            }
        }
    }
    std::cout << encoded.length() << '\n' << cnt_bytes << '\n' << ft.table.size() * sizeof(ft.table[0]) + sizeof(extra_bits) << std::endl;
}
