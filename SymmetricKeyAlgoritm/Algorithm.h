#pragma once
#include <string>
using Algorithm = std::string(*)(const std::string&);

std::string AES_encryptString(const std::string& input);
std::string AES_decryptString(const std::string & input);
std::string IDEA_EncryptString(const std::string& input);
std::string IDEA_DecryptString(const std::string& input);
/// Так же как у меня пищите название функции шифрования (она принимает строку и возвращает строку)
/// И название функции дешифрования (она принимает строку и возвращает строку ВАЖНО!!! строка это ваш шифр)
