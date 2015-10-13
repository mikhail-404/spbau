#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

typedef unsigned char byte;
const size_t MAX_TABLE = 256;

std::vector <std::string> res(MAX_TABLE);

class TreeNode
{
public:
    TreeNode(byte value = '\0', size_t sum = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
            : m_value(value), m_total_sum(sum), m_left(left), m_right(right)
    {}

    static void print(TreeNode* node)
    {
        std::string code("");
        recursive_print(node, 0, code);
    }

    static void recursive_print(TreeNode* node, size_t k, const std::string code)
    {
        if (node == nullptr)
            return;
        recursive_print(node->m_left, k + 1, code + "0");
        if (!(node->m_left && node->m_right))
        {
            res[(size_t)node->m_value] = code;
        }
        recursive_print(node->m_right, k + 1, code + "1");
    }

    static void create_path(TreeNode *node, const std::string &path, uint8_t char_code)
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

    byte m_value;
    size_t m_total_sum = 0;
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

std::string convert_to_string(uint64_t number, uint8_t length)
{
    std::string binary_result(length, '0');
    int k = (int)length;
    while (number)
    {
        binary_result[--k] = char(number % 2 + 48);
        number >>= 1;
    }
    return binary_result;
}

uint64_t set_bit(uint64_t number, uint8_t i)
{
    return number | ((uint64_t)1 << i);
}

uint8_t get_bit(uint64_t number, uint8_t i)
{
    return static_cast <uint8_t>((number & (static_cast <uint64_t>(1) << i)) != 0);
}

uint64_t clear_bit(uint64_t number, uint8_t i)
{
    uint64_t mask = ~(static_cast <uint64_t>(1) << i);
    return number & mask;
}

uint64_t clear_all_bits(uint64_t number, uint8_t i)
{
    uint64_t mask = ~(((uint64_t)1 << (i + 1)) - 1);
    return number & mask;
}

// 01111_{2} = 15_{10}
uint64_t convert_to_ulong(const std::string &code)
{
    uint64_t result_number = 0;

    for(size_t i = 0; i < code.length(); ++i)
    {
        if (code[i] == '1')
            result_number = set_bit(result_number, code.length() - i - 1);
        else
            result_number = clear_bit(result_number, code.length() - i - 1);
    }

    return result_number;
}

int main()
{
    std::ifstream in("/home/mikhail/images/11.deb", std::ios::binary | std::ios::in);

    if (!in.is_open())
    {
        std::cout << "File is not found" << std::endl;
        return -1;
    }

    std::vector <size_t> statistics(MAX_TABLE, 0);
    byte current_byte;
    while (!in.eof())
    {
        current_byte = in.get();
        if (!in.eof())
        {
            ++statistics[current_byte];
        }
    }

    std::priority_queue <TreeNode*, std::vector<TreeNode*>, NodeComparator> q;

    for(size_t i = 0; i < statistics.size(); ++i)
        if (statistics[i])
            q.push(new TreeNode((byte)i, statistics[i]));

    TreeNode* result_node = nullptr;

    size_t count_nodes = q.size();

    if (q.size() == 1)
    {
        result_node = q.top();
        q.pop();
        res[(size_t)result_node->m_value] = "0";
    }
    else if (q.size() > 1)
    {
        while (q.size() != 1)
        {
            TreeNode *a = q.top();
            q.pop();
            TreeNode *b = q.top();
            q.pop();
            q.push(new TreeNode('\0', a->m_total_sum + b->m_total_sum, a, b));
        }
        result_node = q.top();
        q.pop();

        // code compute
        TreeNode::print(result_node);
    }

    std::ofstream out("/home/mikhail/images/3_1.bin", std::ios::binary | std::ios::out);

    //std::cout << "Table size: " << count_nodes << std::endl;
    out.write((char*)&count_nodes, sizeof(count_nodes));

    for(size_t i = 0; i < res.size(); ++i)
        if (!res[i].empty())
        {
            byte current_byte = static_cast<byte>(i);
            out.write((char*)&current_byte, sizeof(current_byte));
            byte length_byte = static_cast<byte>(res[i].length());
            out.write((char*)&length_byte, sizeof(length_byte));
            uint64_t result_number = convert_to_ulong(res[i]);
            out.write((char*)&result_number, sizeof(result_number));
            //std::cout << i << ": " << res[i] << " " << (int)length_byte << " -> " << result_number << std::endl;
        }

    in.clear();
    in.seekg(0, std::ios::beg);

    // получаем результат файла в бинарном виде
    std::string accumulate_result_string("");

    //
    std::ofstream tt1("/home/mikhail/images/1.res", std::ios::out);
    //
    while (!in.eof())
    {
        current_byte = in.get();
        if (!in.eof())
        {
            accumulate_result_string += res[current_byte];
        }
    }

    byte length = 0;
    uint64_t result_number_code = 0;
    for(size_t i = 0; i < accumulate_result_string.length() / 64; ++i)
    {
        length = 64;
        out.write((char*)&length, sizeof(length));
        std::string temp_code(accumulate_result_string, i * 64, 64);
        result_number_code = convert_to_ulong(temp_code);
        out.write((char*)&result_number_code, sizeof(result_number_code));
        //std::cout << temp_code.length() << " -> " << temp_code << std::endl;
        //std::cout << (size_t)length << " " << result_number_code << std::endl;
    }
    if (accumulate_result_string.length() % 64)
    {
        std::string temp_code(accumulate_result_string, accumulate_result_string.length() / 64 * 64);
        //std::cout << temp_code.length() << " -> " << temp_code << std::endl;
        length = temp_code.length();
        result_number_code = convert_to_ulong(temp_code);
        out.write((char *) &length, sizeof(length));
        out.write((char *) &result_number_code, sizeof(result_number_code));
        //std::cout << (size_t)length << " " << result_number_code << std::endl;
    }

    in.close();
    out.close();

    //std::cout << " -------- D E C O D E ---------- " << std::endl;
    // ================================================================================== D E C O D E ==============

    in.open("/home/mikhail/images/3_1.bin", std::ios::binary | std::ios::in);
    std::ofstream out2("/home/mikhail/images/111.deb", std::ios::binary | std::ios::out );

    size_t table_size = 0;
    in.read((char*)&table_size, sizeof(table_size));
    //std::cout << "Table size: " << table_size << std::endl;

    TreeNode* huffman_tree = new TreeNode();

    for(size_t i = 0; i < table_size; ++i)
    {
        uint8_t current_char = 0;
        in.read((char*)&current_char, sizeof(current_char));
        uint8_t current_length = 0;
        in.read((char*)&current_length, sizeof(current_length));
        uint64_t result_number_cur = 0;
        in.read((char*)&result_number_cur, sizeof(result_number_cur));
        std::string result = convert_to_string(result_number_cur, current_length);
        //std::cout << (size_t)current_char << ": " << result << " " << (size_t)current_length << " -> " << result_number_cur << std::endl;

        // create path to current code
        TreeNode::create_path(huffman_tree, result, current_char);
    }

    std::string result_string_decode("");
    while (!in.eof())
    {
        in.read((char*)&length, sizeof(length));
        in.read((char*)&result_number_code, sizeof(result_number_code));
        if (!in.eof())
        {
            //std::cout << (size_t)length << " " << result_number_code << std::endl;
            std::string code_number = convert_to_string(result_number_code, length);
            result_string_decode += code_number;
        }
    }
    //std::cout << "Result: " << result_string_decode << std::endl;

    in.close();


    TreeNode::print(huffman_tree);
    //
    out.close();

    //std::cout << result_string_decode.length() << " vs. " << accumulate_result_string.length() << std::endl;
    int c = 0;
    for(size_t i = 0; i < result_string_decode.length(); ++i)
        if (result_string_decode[i] != accumulate_result_string[i])
            ++c;
    //std::cout << c << std::endl;

    TreeNode* temp = huffman_tree;
    size_t index = 0;

    //
    std::ofstream tt2("/home/mikhail/images/2.res", std::ios::out);
    //
    while (index <= result_string_decode.length())
    {
        if (temp->m_left == nullptr && temp->m_right == nullptr)
        {
            byte current_leaf_node_value = temp->m_value;
            //std::cout << (size_t)current_leaf_node_value << std::endl;
            //std::cout << sizeof(current_leaf_node_value) << std::endl;
            out2.write((char*)&current_leaf_node_value, sizeof(current_leaf_node_value));
            //tt2 << (size_t)current_leaf_node_value << std::endl;
            temp = huffman_tree;
        }

        if (result_string_decode[index] == '0')
            temp = temp->m_left;
        else if (result_string_decode[index] == '1')
            temp = temp->m_right;
        ++index;
    }

    out2.close();

    tt1.close();
    tt2.close();

    return 0;
}