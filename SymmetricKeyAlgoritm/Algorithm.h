#pragma once
#include <string>
using Algorithm = std::string(*)(const std::string&);

std::string AES_encryptString(const std::string& input);
std::string AES_decryptString(const std::string & input);
std::string IDEA_EncryptString(const std::string& input);
std::string IDEA_DecryptString(const std::string& input);
/// ��� �� ��� � ���� ������ �������� ������� ���������� (��� ��������� ������ � ���������� ������)
/// � �������� ������� ������������ (��� ��������� ������ � ���������� ������ �����!!! ������ ��� ��� ����)
