#include "huffman_tree.h"
#include <iostream>

using namespace Huffman;


TreeNode::TreeNode(TreeNode *lc, TreeNode *rc, int cnt) : left_child(lc), right_child(rc), cnt(cnt) {}

TreeNode::TreeNode(TreeNode *lc, TreeNode *rc, int cnt, char c1) : TreeNode(lc, rc, cnt) {
    c = c1;
}

TreeNode::~TreeNode() {
    delete left_child;
    delete right_child;
}

FrequencyTable::FrequencyTable(const std::string &input) {
    build_table(input);
}

void FrequencyTable::build_table(const std::string &input) noexcept {
    for (auto e : input)
        table[(unsigned char)e]++;
}


HuffTree::HuffTree(const FrequencyTable &ft) {
    for (std::size_t i = 0; i < ft.table.size(); i++) {
        if (ft.table[i] > 0)
            nodes.insert(new TreeNode(nullptr, nullptr, ft.table[i], (char) i));
    }
    while (nodes.size() > 1)
        merge_nodes();
    if (nodes.size() == 1)
        root = *nodes.begin();
}

void HuffTree::merge_nodes() noexcept {
    TreeNode* min1 = *nodes.begin();
    nodes.erase(nodes.begin());
    TreeNode* min2 = *nodes.begin();
    nodes.erase(nodes.begin());
    nodes.insert(new TreeNode(min1, min2, min1->get_cnt() + min2->get_cnt()));
}

std::array<std::string, NUM_BYTES> HuffTree::calc_codes() const noexcept {
    std::array<std::string, NUM_BYTES> codes;
    if (root != nullptr) {
        std::string start_code;
        if (root->is_leaf())
            start_code += "0";
        dfs(root, codes, start_code);
    }
    return codes;
}

void HuffTree::dfs(TreeNode* node, std::array<std::string, NUM_BYTES> &codes, std::string current_code) const noexcept {
    if (node->is_leaf()) {
        codes[(unsigned char)node->get_symbol()] = current_code;
        return;
    }
    if (node->get_left_child() != nullptr)
        dfs(node->get_left_child(), codes, current_code + "0");
    if (node->get_right_child() != nullptr)
        dfs(node->get_right_child(), codes, current_code + "1");
}

HuffTree::~HuffTree() {
    delete root;
}
