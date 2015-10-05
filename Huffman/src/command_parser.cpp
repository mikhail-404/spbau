#include "../include/command_parser.hpp"

GetOptions::GetOptions(int argc, char *argv[])
{
    init(argc, argv);
}

void GetOptions::init(int argc, char *argv[])
{
    desc.add_options()
        ("help",                                                    "Помощь")
        ("compress,c",                                              "Архивирование")
        ("uncompress,u",                                            "Разархивирование")
        ("file,f",   boost::program_options::value <std::string>(), "Название входного файла")
        ("output,o", boost::program_options::value <std::string>(), "Название результирующего файла");

    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
    {
        return;
    }

    if (vm.count("compress"))
    {
        m_compress = true;
    }

    if (vm.count("uncompress"))
    {
        m_uncompress = true;
    }

    if (vm.count("file"))
    {
        m_input_filename = vm["file"].as<std::string>();
    }

    if (vm.count("output"))
    {
        m_output_filename = vm["output"].as<std::string>();
    }

    boost::program_options::notify(vm);
}

bool GetOptions::is_compress() const
{
    return m_compress;
}

bool GetOptions::is_uncompress() const
{
    return m_uncompress;
}

std::string GetOptions::input_file() const
{
    return m_input_filename;
}

std::string GetOptions::output_file() const
{
    return m_output_filename;
}
