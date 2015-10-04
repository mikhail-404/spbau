#include "../include/huffman_tree.hpp"

#include <queue>
#include <vector>

//
class TreeNodeComparator : public std::binary_function <TreeNode*, TreeNode*, bool>
{
public:
    bool operator()(const TreeNode *a, const TreeNode *b) const
    {
        return a->total_sum() > b->total_sum();
    }
};

HuffmanTree::HuffmanTree(const std::map <char, int> &dictionary)
{
    //
    m_root = nullptr;
    create_tree_by_dictionary(dictionary);
}

HuffmanTree::~HuffmanTree()
{
    TreeNode::destroy(m_root);
}

void HuffmanTree::create_tree_by_dictionary(const std::map <char, int> &dictionary)
{
    // создадим очередь на минимум
    std::priority_queue <TreeNode*, std::vector <TreeNode*>, TreeNodeComparator> tree_nodes_queue;
    //
    for(std::map <char, int>::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        tree_nodes_queue.push(new TreeNode(it->first, it->second));
    }

    //
    while (tree_nodes_queue.size() != 1)
    {
        TreeNode *first_min  = tree_nodes_queue.top();
        tree_nodes_queue.pop();
        if (!tree_nodes_queue.empty())
        {
            TreeNode *second_min = tree_nodes_queue.top();
            tree_nodes_queue.pop();
            //
            tree_nodes_queue.push(
                new TreeNode('\0', first_min->total_sum() + second_min->total_sum(), first_min, second_min)
            );
        }
    }

    m_root = tree_nodes_queue.top();
}

void HuffmanTree::codes() const
{
    std::string result_code("");
    TreeNode::get_huffman_code(m_root, result_code);
}
