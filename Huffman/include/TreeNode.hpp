//
// Created by mikhail on 10/13/15.
//

#ifndef HUFFMAN_CODE_TREENODE_HPP
#define HUFFMAN_CODE_TREENODE_HPP

#include <string>
#include <vector>

class TreeNode
{
public:
    TreeNode(uint8_t value = '\0', size_t sum = 0, TreeNode* left = nullptr, TreeNode* right = nullptr);

    static void print          (TreeNode*, std::vector <std::string> &);
    static void recursive_print(TreeNode*, size_t, const std::string, std::vector <std::string> &);
    static void create_path    (TreeNode*, const std::string &, uint8_t);

    static void destroy(TreeNode*);

    uint8_t   m_value;
    size_t    m_total_sum = 0;
    TreeNode* m_left;
    TreeNode* m_right;
};

class NodeComparator : public std::binary_function <TreeNode*, TreeNode*, bool>
{
public:
    bool operator()(const TreeNode* a, const TreeNode* b) const
    {
        return a->m_total_sum > b->m_total_sum;
    }
};

#endif //HUFFMAN_CODE_TREENODE_HPP
