#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <iostream>
#include <map>
#include <string>

#include "tree_node.hpp"

class HuffmanTree
{
public:
    HuffmanTree(const std::map <char, int>&);
    ~HuffmanTree();
    std::map <char, std::string> codes() const;

private:
    TreeNode *m_root;
    void create_tree_by_dictionary(const std::map <char, int>&);
};

#endif // HUFFMAN_TREE_HPP
