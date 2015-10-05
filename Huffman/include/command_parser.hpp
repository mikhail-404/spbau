#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <boost/program_options.hpp>

class GetOptions
{
public:
    GetOptions(int, char**);

    bool         is_compress   () const;
    bool         is_uncompress () const;
    std::string  input_file    () const;
    std::string  output_file   () const;

private:
    boost::program_options::options_description desc;
    boost::program_options::variables_map       vm;

    bool         m_compress;
    bool         m_uncompress;
    std::string  m_input_filename;
    std::string  m_output_filename;

    void         init(int, char**);
};

#endif // COMMAND_PARSER_HPP
