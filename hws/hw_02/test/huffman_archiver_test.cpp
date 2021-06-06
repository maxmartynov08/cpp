#include "doctest.h"
#include "huffman_archiver.h"
#include "util.h"

using namespace Huffman;


TEST_CASE("Encoder tests") {
    std::array<std::string, NUM_BYTES> codes;
    codes['a' - '\0'] = "100";
    codes['b' - '\0'] = "101";
    codes['c' - '\0'] = "0";
    codes['d' - '\0'] = "11";
    auto e = Encoder(codes);
    SUBCASE("Empty string") {
        CHECK_EQ(e.encode(""), "");
    }
    SUBCASE("Without repeats") {
        CHECK_EQ(e.encode("abcd"), "100101011");
    }
    SUBCASE("With repeats") {
        CHECK_EQ(e.encode("abaddcb"), "10010110011110101");
    }
}

TEST_CASE("convert_to_char tests") {
    SUBCASE("< 8 length") {
        CHECK_EQ(convert_to_char("0011"), '0');
        CHECK_EQ(convert_to_char("011001"), 'd');
        CHECK_EQ(convert_to_char("001"), ' ');
    }
    SUBCASE("= 8 length") {
        CHECK_EQ(convert_to_char("00101000"), '(');
        CHECK_EQ(convert_to_char("01100001"), 'a');
        CHECK_EQ(convert_to_char("01111101"), '}');
    }
}

TEST_CASE("archive tests") {
    HuffmanArchiver ha;
    std::string output_file = "test/test_data1/output.bin";
    SUBCASE("Empty file") {
        ha.archive("test/test_data1/empty.txt", output_file);
        CHECK(compare_files(output_file, "test/test_data1/empty_res.bin"));
    }
    SUBCASE("One letter file") {
        ha.archive("test/test_data1/one_letter.txt", output_file);
        CHECK(compare_files(output_file, "test/test_data1/one_letter_res.bin"));
    }
    SUBCASE("Normal .txt file") {
        ha.archive("test/test_data1/normalt.txt", output_file);
        CHECK(compare_files(output_file, "test/test_data1/normalt_res.bin"));
    }
    SUBCASE("Normal .bin file") {
        ha.archive("test/test_data1/normalb.bin", output_file);
        CHECK(compare_files(output_file, "test/test_data1/normalb_res.bin"));
    }
    SUBCASE("Non-existent input file") {
        ha.archive("ggwp.txt", output_file);
        CHECK(compare_files(output_file, "test/test_data1/normalb_res.bin"));
    }
}
