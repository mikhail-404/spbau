//
// Created by mikhail on 10/13/15.
//

#ifndef HUFFMAN_CODE_HUFFMANCODEEXCEPTION_HPP
#define HUFFMAN_CODE_HUFFMANCODEEXCEPTION_HPP

#include <stdexcept>

class FileIsNotFoundException : public std::exception
{
public:
    FileIsNotFoundException(char const* message)
            : m_message(message)
    {}
    virtual const char* what()
    {
        return m_message;
    }

private:
    char const* m_message;
};

#endif //HUFFMAN_CODE_HUFFMANCODEEXCEPTION_HPP
