#ifndef BINARY_READER_HPP
#define BINARY_READER_HPP

#include <fstream>
#include <map>
#include <string>
#include <iostream>

//
std::string int_to_binary_format(int);
//
void cut_code(std::string &, unsigned char);
//
void decoder(std::ifstream &, std::ofstream &);

#endif // BINARY_READER_HPP
