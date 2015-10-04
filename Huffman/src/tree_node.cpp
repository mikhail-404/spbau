#include "../include/tree_node.hpp"

TreeNode::TreeNode(const tree_node_value value, const size_t sum, TreeNode *left, TreeNode *right)
        : m_root_value(value), m_total_sum(sum), m_left(left), m_right(right)
    {}

TreeNode::tree_node_value TreeNode::value() const
{
    return m_root_value;
}

size_t TreeNode::total_sum() const
{
    return m_total_sum;
}

void TreeNode::print_tree(TreeNode *node)
{
    recursive_print_tree(node, 4);
}

bool TreeNode::is_leaf(const TreeNode *node)
{
    return node->m_left == nullptr && node->m_right == nullptr;
}

void TreeNode::get_huffman_code(const TreeNode *node, std::string code)
{
    if (is_leaf(node))
        std::cout << node->value() << ": " << code << std::endl;
    else
    {
        get_huffman_code(node->m_left, code + "0");
        get_huffman_code(node->m_right, code + "1");
    }
}

void TreeNode::destroy(TreeNode *node)
{
    if (!node)
        return;
    destroy(node->m_left);
    destroy(node->m_right);
    delete node;
}

void TreeNode::recursive_print_tree(TreeNode *root, int shift)
{
    if (root)
    {
        if (root->m_left)
            recursive_print_tree(root->m_left, shift + 3);
        for(int i = 0; i < shift; ++i)
            std::cout << " ";
        std::cout << root->m_root_value << std::endl;
        if (root->m_right)
            recursive_print_tree(root->m_right, shift + 3);
    }
}
