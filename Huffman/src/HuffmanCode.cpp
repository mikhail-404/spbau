#include "HuffmanCode.hpp"
#include "HuffmanCodeException.hpp"

#include <vector>

HuffmanCode::HuffmanCode(const std::string &input_filename, const std::string &output_filename)
    : m_input_file(input_filename), m_output_file(output_filename)
{
}

void HuffmanCode::encode()
{
    std::ifstream in(m_input_file, std::ios::binary | std::ios::in);
    std::ofstream out(m_output_file, std::ios::binary | std::ios::out);

    if (!in.is_open())
    {
        throw FileIsNotFoundException("File is not found!");
    }

    std::vector <size_t> statistics(MAX_TABLE, 0);
    uint8_t current_byte;
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
            q.push(new TreeNode((uint8_t)i, statistics[i]));

    TreeNode* result_node = nullptr;

    size_t count_nodes = q.size();

    std::vector <std::string> code_results(MAX_TABLE, "");

    if (q.size() == 1)
    {
        result_node = q.top();
        q.pop();
        code_results[(size_t)result_node->m_value] = "0";
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

        TreeNode::print(result_node, code_results);
    }

    out.write((char*)&count_nodes, sizeof(count_nodes));

    for(size_t i = 0; i < code_results.size(); ++i)
        if (!code_results[i].empty())
        {
            uint8_t current_byte = static_cast<uint8_t>(i);
            out.write((char*)&current_byte, sizeof(current_byte));
            uint8_t length_byte = static_cast<uint8_t>(code_results[i].length());
            out.write((char*)&length_byte, sizeof(length_byte));
            uint64_t result_number = convert_to_ulong(code_results[i]);
            out.write((char*)&result_number, sizeof(result_number));
        }

    in.clear();
    in.seekg(0, std::ios::beg);

    std::string accumulate_result_string("");

    while (!in.eof())
    {
        current_byte = in.get();
        if (!in.eof())
        {
            accumulate_result_string += code_results[current_byte];
        }
    }

    uint8_t length = 0;
    uint64_t result_number_code = 0;
    for(size_t i = 0; i < accumulate_result_string.length() / 64; ++i)
    {
        length = 64;
        out.write((char*)&length, sizeof(length));
        std::string temp_code(accumulate_result_string, i * 64, 64);
        result_number_code = convert_to_ulong(temp_code);
        out.write((char*)&result_number_code, sizeof(result_number_code));
    }

    if (accumulate_result_string.length() % 64)
    {
        std::string temp_code(accumulate_result_string, accumulate_result_string.length() / 64 * 64);
        length = temp_code.length();
        result_number_code = convert_to_ulong(temp_code);
        out.write((char *) &length, sizeof(length));
        out.write((char *) &result_number_code, sizeof(result_number_code));
    }

    in.close();
    out.close();
}

void HuffmanCode::decode()
{
    std::ifstream in(m_input_file, std::ios::binary | std::ios::in);
    std::ofstream out(m_output_file, std::ios::binary | std::ios::out );

    if (!in.is_open())
    {
        throw FileIsNotFoundException("File is not found!");
    }

    size_t table_size = 0;
    in.read((char*)&table_size, sizeof(table_size));

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
        TreeNode::create_path(huffman_tree, result, current_char);
    }

    std::string result_string_decode("");
    uint8_t length;
    uint64_t result_number_code;
    while (!in.eof())
    {
        in.read((char*)&length, sizeof(length));
        in.read((char*)&result_number_code, sizeof(result_number_code));
        if (!in.eof())
        {
            std::string code_number = convert_to_string(result_number_code, length);
            result_string_decode += code_number;
        }
    }

    in.close();

    std::vector <std::string> code_results(MAX_TABLE, "");
    TreeNode::print(huffman_tree, code_results);

    TreeNode* temp = huffman_tree;
    size_t index = 0;

    while (index <= result_string_decode.length())
    {
        if (temp->m_left == nullptr && temp->m_right == nullptr)
        {
            uint8_t current_leaf_node_value = temp->m_value;
            out.write((char*)&current_leaf_node_value, sizeof(current_leaf_node_value));
            temp = huffman_tree;
        }

        if (result_string_decode[index] == '0')
            temp = temp->m_left;
        else if (result_string_decode[index] == '1')
            temp = temp->m_right;
        ++index;
    }

    out.close();
}