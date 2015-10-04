#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <iostream>
#include <map>

#include "tree_node.hpp"

class HuffmanTree
{
public:
    //
    HuffmanTree(const std::map <char, int>&);
    //
    ~HuffmanTree();
    //
    void codes() const;

private:
    //
    TreeNode *m_root;
    //
    void create_tree_by_dictionary(const std::map <char, int>&);
};

#endif // HUFFMAN_TREE_HPP
