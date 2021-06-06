#include "huffman_archiver.h"
#include "huffman_unarchiver.h"
#include <tuple>

using namespace Huffman;


std::tuple<std::string, std::string, std::string> parse_arguments(int argc, char** argv) {
    int num_args = 6;
    if (argc < num_args)
        throw std::invalid_argument("Wrong arguments!\n");
    std::string mode, input_file, output_file;
    for (int i = 1; i < num_args; i++) {
        std::string arg(argv[i]);
        if (arg == "-c")
            mode = "archive";
        else if (arg == "-u")
            mode = "unarchive";
        else if ((arg == "-f" || arg == "--file") && i < num_args - 1) {
            input_file = argv[i + 1];
            i++;
        }
        else if ((arg == "-o" || arg == "--output") && i < num_args - 1) {
            output_file = argv[i + 1];
            i++;
        }
        else
            throw std::invalid_argument("Wrong arguments!\n");
    }
    if (mode.empty() || input_file.empty() || output_file.empty())
        throw std::invalid_argument("Wrong arguments!\n");

    return std::make_tuple(mode, input_file, output_file);
}

int main(int argc, char** argv) {
    try {
        auto args = parse_arguments(argc, argv);
        if (std::get<0>(args) == "archive") {
            HuffmanArchiver h;
            h.archive(std::get<1>(args), std::get<2>(args));
        }
        else {
            HuffmanUnarchiver hu;
            hu.unarchive(std::get<1>(args), std::get<2>(args));
        }
    } catch(const std::invalid_argument &e) {
        std::cout << e.what();
    }
    return 0;
}
