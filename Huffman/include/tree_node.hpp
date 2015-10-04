#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

class TreeNode
{
public:
    typedef char        tree_node_value;
    //
    TreeNode(const tree_node_value value = '\0', const size_t sum = 0, TreeNode *left = nullptr, TreeNode *right = nullptr);
    //
    tree_node_value value() const;
    //
    size_t total_sum() const;
    //
    static void print_tree(TreeNode *node);
    //
    static bool is_leaf(const TreeNode *node);
    //
    static void get_huffman_code(const TreeNode *node, std::string code);
    //
    static void destroy(TreeNode *node);

private:
    //
    tree_node_value     m_root_value;
    //
    size_t              m_total_sum;
    //
    TreeNode            *m_left;
    //
    TreeNode            *m_right;
    //
    static void recursive_print_tree(TreeNode *root, int shift);
};

#endif // TREE_NODE_HPP
