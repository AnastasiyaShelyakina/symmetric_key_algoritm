#pragma once
#include <string>
using Algorithm = std::string(*)(const std::string&);

std::string RS5_encryptString(const std::string& input);
std::string RS5_decryptString(const std::string& input);