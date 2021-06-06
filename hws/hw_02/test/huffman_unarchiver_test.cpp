#include "doctest.h"
#include "huffman_unarchiver.h"
#include "util.h"

using namespace Huffman;


TEST_CASE("archive tests") {
    HuffmanUnarchiver hu;
    std::string output_file_txt = "test/test_data1/output.txt";
    std::string output_file_bin = "test/test_data1/output.bin";
    SUBCASE("Empty file") {
        hu.unarchive("test/test_data2/empty_res.bin", output_file_txt);
        CHECK(compare_files(output_file_txt, "test/test_data2/empty.txt"));
    }
    SUBCASE("One letter file") {
        hu.unarchive("test/test_data2/one_letter_res.bin", output_file_txt);
        CHECK(compare_files(output_file_txt, "test/test_data2/one_letter.txt"));
    }
    SUBCASE("Normal .txt file") {
        hu.unarchive("test/test_data2/normalt_res.bin", output_file_txt);
        CHECK(compare_files(output_file_txt, "test/test_data2/normalt.txt"));
    }
    SUBCASE("Normal .bin file") {
        hu.unarchive("test/test_data2/normalb_res.bin", output_file_bin);
        CHECK(compare_files(output_file_bin, "test/test_data2/normalb.bin"));
    }
    SUBCASE("Non-existent input file") {
        hu.unarchive("ggwp.txt", output_file_txt);
        CHECK(compare_files(output_file_bin, "test/test_data2/normalb.bin"));
    }
}
