#pragma once
#include <cstddef>
#include <set>
#include <string>
#include <algorithm>
#include <array>
#include <memory>


namespace Huffman {

    const std::size_t NUM_BYTES = 256;
    const std::size_t BYTE_SIZE = 8;

    class TreeNode {
    public:
        TreeNode(TreeNode *lc, TreeNode *rc, int cnt);

        TreeNode(TreeNode *lc, TreeNode *rc, int cnt, char c);

        ~TreeNode();

        TreeNode* get_left_child() const noexcept { return left_child; };

        TreeNode* get_right_child() const noexcept { return right_child; };

        int get_cnt() const noexcept { return cnt; };

        char get_symbol() const noexcept { return c; };

        bool is_leaf() const noexcept { return left_child == nullptr && right_child == nullptr; };

    private:
        TreeNode *left_child;
        TreeNode *right_child;
        int cnt;
        char c;
    };

    struct TreeNodeComparator {
        bool operator()(const TreeNode *a, const TreeNode *b) const {
            return a->get_cnt() < b->get_cnt();
        }
    };


    class FrequencyTable {
    public:
        FrequencyTable() {};

        FrequencyTable(const std::string &str);

        void build_table(const std::string &input) noexcept;

    public:
        std::array<std::size_t, NUM_BYTES> table{};
    };


    class HuffTree {
    public:
        ~HuffTree();

        explicit HuffTree(const FrequencyTable &ft);

        std::array<std::string, NUM_BYTES> calc_codes() const noexcept;

    private:
        void merge_nodes() noexcept;

        void dfs(TreeNode *node, std::array<std::string, NUM_BYTES> &codes, std::string current_code) const noexcept;

    private:
        std::multiset<TreeNode *, TreeNodeComparator> nodes;
        TreeNode *root = nullptr;
    };
}
