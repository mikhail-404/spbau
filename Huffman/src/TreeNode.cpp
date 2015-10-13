#include "TreeNode.hpp"

TreeNode::TreeNode(uint8_t value, size_t sum, TreeNode* left, TreeNode* right)
    : m_value(value), m_total_sum(sum), m_left(left), m_right(right)
{

}

void TreeNode::print(TreeNode* node, std::vector <std::string> &code_result)
{
    std::string code("");
    recursive_print(node, 0, code, code_result);
}

void TreeNode::recursive_print(TreeNode* node, size_t k, const std::string code, std::vector <std::string> &code_result)
{
    if (node == nullptr)
        return;
    recursive_print(node->m_left, k + 1, code + "0", code_result);
    if (!(node->m_left && node->m_right))
    {
        code_result[(size_t)node->m_value] = code;
    }
    recursive_print(node->m_right, k + 1, code + "1", code_result);
}

void TreeNode::create_path(TreeNode *node, const std::string &path, uint8_t char_code)
{
    TreeNode *current_pointer = node;
    for(size_t i = 0; i < path.length(); ++i)
    {
        if (path[i] == '1')
        {
            if (!current_pointer->m_right)
                current_pointer->m_right = new TreeNode();
            current_pointer = current_pointer->m_right;
        }
        else
        {
            if (!current_pointer->m_left)
                current_pointer->m_left = new TreeNode();
            current_pointer = current_pointer->m_left;
        }
    }
    current_pointer->m_value = char_code;
    node = current_pointer;
}