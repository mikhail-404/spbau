#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP

#include <fstream>
#include <map>
#include <string>

int  convert                      (const std::string &                                           );
void binary_write_table_frequency (std::ofstream &, const std::map <char, std::string> &         );
void binary_write_text            (std::ifstream &, std::ofstream &, std::map <char, std::string>);
void encoder                      (std::ifstream &, std::ofstream &                              );

#endif // BINARY_WRITER_HPP
