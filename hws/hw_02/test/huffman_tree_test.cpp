#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "huffman_tree.h"

using namespace Huffman;


TEST_CASE("TreeNode tests") {
    TreeNode* ch1 = new TreeNode(nullptr, nullptr, 100500, 'a');
    TreeNode* ch2 = new TreeNode(nullptr, nullptr, 1, '?');
    TreeNode p = TreeNode(ch1, ch2, 100501);
    SUBCASE("Not leaf") {
        CHECK_EQ(p.get_left_child(), ch1);
        CHECK_EQ(p.get_right_child(), ch2);
        CHECK_EQ(p.get_cnt(), 100501);
        CHECK_FALSE(p.is_leaf());
    }
    SUBCASE("Leaf") {
        CHECK_EQ(ch1->get_left_child(), nullptr);
        CHECK_EQ(ch1->get_symbol(), 'a');
        CHECK(ch2->is_leaf());
    }
}

TEST_CASE("TreeNodeComparator tests") {
    TreeNode* tn1 = new TreeNode(nullptr, nullptr, 1);
    TreeNode* tn2 = new TreeNode(nullptr, nullptr, 2);
    TreeNode* tn3 = new TreeNode(nullptr, nullptr, 1, '?');
    TreeNodeComparator cmp;
    CHECK(cmp(tn1, tn2));
    CHECK_FALSE(cmp(tn1, tn3));
    delete tn1; delete tn2; delete tn3;
}

TEST_CASE("FrequencyTable tests") {
    SUBCASE("Empty string") {
        auto ft = FrequencyTable("");
        for (auto e : ft.table)
            CHECK_EQ(e, 0);
    }
    SUBCASE("One letter string") {
        auto ft = FrequencyTable("aaaaa");
        for (std::size_t i = 0; i < ft.table.size(); i++)
            if ('\0' + i == 'a') CHECK_EQ(ft.table[i], 5); else CHECK_EQ(ft.table[i], 0);
    }
    SUBCASE("Just string") {
        auto ft = FrequencyTable("aAbb.a...b");
        CHECK_EQ(ft.table['a' - '\0'], 2);
        CHECK_EQ(ft.table['A' - '\0'], 1);
        CHECK_EQ(ft.table['b' - '\0'], 3);
        CHECK_EQ(ft.table['.' - '\0'], 4);
    }
}

TEST_CASE("HuffTree tests") {
    std::array<std::string, NUM_BYTES> codes;
    SUBCASE("Empty string") {
        auto ht = HuffTree(FrequencyTable(""));
        codes = ht.calc_codes();
        for (auto e : codes)
            CHECK_EQ(e, "");
    }
    SUBCASE("One letter string") {
        auto ht = HuffTree(FrequencyTable("aaaaa"));
        codes = ht.calc_codes();
        for (std::size_t i = 0; i < codes.size(); i++)
            if ('\0' + i == 'a') CHECK_EQ(codes[i], "0"); else CHECK_EQ(codes[i], "");
    }
    SUBCASE("Just string #1") {
        auto ht = HuffTree(FrequencyTable("abbccccddddd")); // 'a'-1, 'b'-2, 'c'-4, 'd'-5
        codes = ht.calc_codes();
        CHECK_EQ(codes['a' - '\0'], "100");
        CHECK_EQ(codes['b' - '\0'], "101");
        CHECK_EQ(codes['c' - '\0'], "11");
        CHECK_EQ(codes['d' - '\0'], "0");
    }
    SUBCASE("Just string #2") {
        auto ht = HuffTree(FrequencyTable("abbccccdddddeeeeeeffffffff")); // 'a'-1, 'b'-2, 'c'-4, 'd'-5, 'e'-6, 'f'-8
        codes = ht.calc_codes();
        CHECK_EQ(codes['a' - '\0'], "1000");
        CHECK_EQ(codes['b' - '\0'], "1001");
        CHECK_EQ(codes['c' - '\0'], "101");
        CHECK_EQ(codes['d' - '\0'], "00");
        CHECK_EQ(codes['e' - '\0'], "01");
        CHECK_EQ(codes['f' - '\0'], "11");
    }
}
